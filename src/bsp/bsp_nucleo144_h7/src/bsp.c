/**
******************************************************************************
* @file           : bsp.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2023 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2023 FaraabinCo.
* All rights reserved.</center></h2>
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
* @verbatim
* @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "bsp_sys.h"

#include "Ethernet\socket.h"
#include "ex\ex_tcp_udp_server.h"

#include "stm32h7xx_phal.h"
#include "faraabin.h"

#include "chrono.h"

/* Private define ------------------------------------------------------------*/
#define LED_RED_PIN                           Phal.Gpio->PB14
#define LED_GREEN_PIN                         Phal.Gpio->PB0
#define LED_BLUE_PIN                          Phal.Gpio->PB7
#define PB_USER_PIN                           Phal.Gpio->PC13

#define USB2SERIAL_UART                       Phal.Uart->Uart3

#define WIZNET_SPI                            Phal.Spi->Spi1
#define WIZNET_CS_PIN                         Phal.Gpio->PA11

#define FARAABIN_UART_BAUDRATE                115200
#define FARAABIN_UART_BUFFER_SIZE             500
#define FARAABIN_UART_IDLE_DETECTION_BIT_QTY  12
#define FARAABIN_UART_RX_TIMEOUT_ms           5000
#define FARAABIN_UART_TX_TIMEOUT_ms           500

#define WIZNET_IP_TYPE                        NETINFO_STATIC
#define WIZNET_MAC                            { 0xEA, 0x11, 0x22, 0x33, 0x44, 110 }
#define WIZNET_IP                             { 192, 168, 1, 110 }
#define WIZNET_SUBNET_MASK                    { 255, 255, 255, 0 }
#define WIZNET_GATEWAY                        { 192, 168, 20, 1 }
#define WIZNET_DNS                            { 0, 0, 0, 0 }

#define FARAABIN_SOCKET_NUMBER                0
#define FARAABIN_PORT                         110

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t FbUartRxBuffer[500];
static sChrono FbUartSendingChrono;

/* Private function prototypes -----------------------------------------------*/
static uint8_t BspDioInit(void);
static uint8_t BspSerialInit(void);
static uint8_t BspWiznetInit(void);
static uint8_t BspTimerInit(void);
static void FaraabinUartNewFrameEventCallback(object sender, void* e);
static void FaraabinUartErrorEventCallback(object sender, sSerialErrorOccuredEventArgs *e);
#ifdef FARAABIN_LINK_ETHERNET
static void FaraabinEthernetNewFrameEventCallback(uint8_t *data, uint16_t size);
#endif

static void fW5500_Select(void);
static void fW5500_Unselect(void);
static void fW5500_ReadBuff(uint8_t* buff, uint16_t len);
static void fW5500_WriteBuff(uint8_t* buff, uint16_t len);
static uint8_t fW5500_ReadByte(void);
static void fW5500_WriteByte(uint8_t byte);
static void fW5500_cris_en(void);
static void fW5500_cris_ex(void);

/* Variables -----------------------------------------------------------------*/
sBspNucleo144 Bsp;

/*
===============================================================================
                      ##### bsp.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fBsp_Init(void) {
  
  if(fBspSys_Init() != 0) {
    return 1;
  }
  if(BspSerialInit() != 0) {
    //TODO: Write something here to detect that
  }
  if(fFaraabin_Init() != 0) {
    //TODO: Write something here to detect that
    //"Faraabin" is not initialized on your target.
  }
  
  BspDioInit();
  BspTimerInit();
  BspWiznetInit();
  fLed_Flash(&Bsp.Dio.LedGreen);
  
  return 0;
}

/**
 * @brief 
 * 
 */
void fBsp_Run(void) {
  
  fLed_Run(&Bsp.Dio.LedRed);
  fLed_Run(&Bsp.Dio.LedGreen);
  fLed_Run(&Bsp.Dio.LedBlue);

#ifdef FARAABIN_LINK_ETHERNET
  RUN_EVERY_MS_(ethernet, 10) {
    
    ex_tcp_server(FARAABIN_SOCKET_NUMBER, FARAABIN_PORT, FbUartRxBuffer, sizeof(FbUartRxBuffer), FaraabinEthernetNewFrameEventCallback, false);
    
    RUN_END_;
  }
#endif

}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fBsp_SerialSend(uint8_t *data, uint16_t size) {
  
  fChrono_StartTimeoutMs(&FbUartSendingChrono, FARAABIN_UART_TX_TIMEOUT_ms);
  
#ifdef FARAABIN_LINK_SERIAL
  return fSerial_SendNonBlock_(USB2SERIAL_UART, data, size);
#endif
  
#ifdef FARAABIN_LINK_ETHERNET
  int32_t len = send(FARAABIN_SOCKET_NUMBER, data, size);
  
  if(len != size) {
    return 1;
  }
  
  return 0;
#endif
}

/**
 * @brief 
 * 
 * @return bool 
 */
bool fBsp_SerialIsSending(void) {
  
#ifdef FARAABIN_LINK_SERIAL
  bool res = fSerial_IsSending_(USB2SERIAL_UART);  
  
  if(res == false) {
    return false;
  }
  
  if(fChrono_IsTimeout(&FbUartSendingChrono) == true) {
    return false;
  }
  
  return true;
#endif

#ifdef FARAABIN_LINK_ETHERNET
  return false;
#endif
}

/*
===============================================================================
                      ##### bsp.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t BspDioInit(void) {
  
  Bsp.Dio.LedRed.pPin = LED_RED_PIN;
  Bsp.Dio.LedRed.Invert = false;
  Bsp.Dio.LedRed.Mode = eLED_MODE_FLASH;
  Bsp.Dio.LedRed.OffTimeMs = 500;
  Bsp.Dio.LedRed.OnTimeMs = 500;
  Bsp.Dio.LedRed.OutType = eGPIO_PUSH_PULL;
  fLed_Init(&Bsp.Dio.LedRed);
  
  Bsp.Dio.LedGreen.pPin = LED_GREEN_PIN;
  Bsp.Dio.LedGreen.Invert = false;
  Bsp.Dio.LedGreen.Mode = eLED_MODE_FLASH;
  Bsp.Dio.LedGreen.OffTimeMs = 500;
  Bsp.Dio.LedGreen.OnTimeMs = 500;
  Bsp.Dio.LedGreen.OutType = eGPIO_PUSH_PULL;
  fLed_Init(&Bsp.Dio.LedGreen);
  
  Bsp.Dio.LedBlue.pPin = LED_BLUE_PIN;
  Bsp.Dio.LedBlue.Invert = false;
  Bsp.Dio.LedBlue.Mode = eLED_MODE_FLASH;
  Bsp.Dio.LedBlue.OffTimeMs = 500;
  Bsp.Dio.LedBlue.OnTimeMs = 500;
  Bsp.Dio.LedBlue.OutType = eGPIO_PUSH_PULL;
  fLed_Init(&Bsp.Dio.LedBlue);
  
  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t BspSerialInit(void) {
  
  Bsp.Com.Usb2serial = USB2SERIAL_UART;
  
  USB2SERIAL_UART->Baudrate = FARAABIN_UART_BAUDRATE;
  USB2SERIAL_UART->Parity = eSERIAL_PARITY_NONE;
  USB2SERIAL_UART->StopBits = eSERIAL_STOP_BIT_1;
  USB2SERIAL_UART->pReceiveBuffer = FbUartRxBuffer;
  USB2SERIAL_UART->ReceiveBufferSize = sizeof(FbUartRxBuffer);
  USB2SERIAL_UART->ReceiveTimeoutMs = FARAABIN_UART_RX_TIMEOUT_ms;
  if(fSerial_Open_(USB2SERIAL_UART) != 0) {
    return 1;
  }
  if(fSerial_ReceiveNonBlock_(USB2SERIAL_UART, USB2SERIAL_UART->pReceiveBuffer, USB2SERIAL_UART->ReceiveBufferSize) != 0) {
    return 1;
  }
  if(fSerial_RegisterIdleDetectedEvent_(USB2SERIAL_UART, FARAABIN_UART_IDLE_DETECTION_BIT_QTY, FaraabinUartNewFrameEventCallback) != 0) {
    return 1;
  }
  if(fSerial_RegisterErrorOccuredEvent_(USB2SERIAL_UART, FaraabinUartErrorEventCallback) != 0) {
    return 1;
  }
  
  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t BspWiznetInit(void) {
  
  WIZNET_CS_PIN->Direction = eGPIO_DIR_OUTPUT;
  WIZNET_CS_PIN->OutType = eGPIO_PUSH_PULL;
  fGpio_Init_(WIZNET_CS_PIN);
  fGpio_Set_(WIZNET_CS_PIN);

  WIZNET_SPI->Role = eSPI_ROLE_MASTER;
  WIZNET_SPI->Mode = eSPI_MODE_3;
  WIZNET_SPI->DataSize = 8;
  WIZNET_SPI->BitOrder = eSPI_FIRSTBIT_MSB;
  if(fSpi_Init_(WIZNET_SPI) != 0) {
    return 1;
  }
  
  reg_wizchip_cs_cbfunc(fW5500_Select, fW5500_Unselect);
  reg_wizchip_spi_cbfunc(fW5500_ReadByte, fW5500_WriteByte);
  reg_wizchip_spiburst_cbfunc(fW5500_ReadBuff, fW5500_WriteBuff);
  reg_wizchip_cris_cbfunc(fW5500_cris_en, fW5500_cris_ex);

  uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
  if(wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes) != 0) {
    return 1;
  }
  
  wiz_NetInfo net_info = {
    .mac  = WIZNET_MAC,
    .ip   = WIZNET_IP,
    .sn   = WIZNET_SUBNET_MASK,
    .gw   = WIZNET_GATEWAY,
    .dns  = WIZNET_DNS,
    .dhcp = WIZNET_IP_TYPE
  };
  
  wizchip_setnetinfo(&net_info);
  
  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t BspTimerInit(void) {

  Bsp.SysRt.Tim6 = Phal.Timer->Ch6;
  Bsp.SysRt.Tim7 = Phal.Timer->Ch7;

  return 0;
}

/**
 * @brief 
 * 
 * @param sender 
 * @param e 
 */
static void FaraabinUartNewFrameEventCallback(object sender, void* e) {
  
  uint16_t size = fSerial_ReceiveBuffer_Qty_(USB2SERIAL_UART);
  
#ifdef FARAABIN_LINK_SERIAL
  for(uint16_t i = 0; i < size; i++) {
    
    fFaraabin_CharReceived(USB2SERIAL_UART->pReceiveBuffer[i]);
    
  }
#endif
  
  fSerial_ReceiveNonBlock_(USB2SERIAL_UART, USB2SERIAL_UART->pReceiveBuffer, USB2SERIAL_UART->ReceiveBufferSize);
}

/**
 * @brief 
 * 
 * @param sender 
 * @param e 
 */
static void FaraabinUartErrorEventCallback(object sender, sSerialErrorOccuredEventArgs *e) {
  
  FARAABIN_Printf_("USB2SERIAL_UART ERROR: %d", e->ErrorCode);
  fSerial_ReceiveNonBlock_(USB2SERIAL_UART, USB2SERIAL_UART->pReceiveBuffer, USB2SERIAL_UART->ReceiveBufferSize);

}

/**
 * @brief 
 * 
 * @param data 
 * @param size 
 */
#ifdef FARAABIN_LINK_ETHERNET
static void FaraabinEthernetNewFrameEventCallback(uint8_t *data, uint16_t size) {
  

  for(uint16_t i = 0; i < size; i++) {
    
    fFaraabin_CharReceived(data[i]);
    
  }
}
#endif

/**
 * @brief 
 * 
 */
static void fW5500_Select(void) {
  fGpio_Reset_(WIZNET_CS_PIN);
}

/**
 * @brief 
 * 
 */
static void fW5500_Unselect(void) {
  fGpio_Set_(WIZNET_CS_PIN);
}

/**
 * @brief 
 * 
 * @param buff 
 * @param len 
 */
static void fW5500_ReadBuff(uint8_t* buff, uint16_t len) {
  fSpi_Receive_(WIZNET_SPI, buff, len, 1000);
}

/**
 * @brief 
 * 
 * @param buff 
 * @param len 
 */
static void fW5500_WriteBuff(uint8_t* buff, uint16_t len) {
    fSpi_Transmit_(WIZNET_SPI, buff, len, 1000);
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t fW5500_ReadByte(void) {
  
  uint8_t byte;
  
  fW5500_ReadBuff(&byte, sizeof(byte));
  
  return byte;
}

/**
 * @brief 
 * 
 * @param byte 
 */
static void fW5500_WriteByte(uint8_t byte) {
  fW5500_WriteBuff(&byte, sizeof(byte));
}

/**
 * @brief 
 * 
 */
static void fW5500_cris_en(void) {
}

/**
 * @brief 
 * 
 */
static void fW5500_cris_ex(void) {
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

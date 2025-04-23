/**
******************************************************************************
* @file           : wiz610io_initialize_example.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2022 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2022 FaraabinCo.
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

#include "w6100.h"
#include "wiz610io_cmd.h"

/* Private define ------------------------------------------------------------*/
#define WIZNET_SPI  bsp.com.spi.spi5
#define WIZNET_CS   bsp.com.spi.spi5_cs
#define WIZNET_RST  bsp.io.dio.gpio16

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void DictFunc(void *param);

static void W6100_Select(void);
static void W6100_Unselect(void);
static void W6100_ReadBuff(uint8_t* buff, short len);
static void W6100_WriteBuff(uint8_t* buff, short len);
static uint8_t W6100_ReadByte(void);
static void W6100_WriteByte(uint8_t byte);
static void W6100_cris_en(void);
static void W6100_cris_ex(void);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
          ##### wiz610io_initialize_example.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t wiz610io_initialize(void) {
  
  WIZNET_CS->u_dir = eGPIO_DIR_OUTPUT;
  WIZNET_CS->u_out_type = eGPIO_PUSH_PULL;
  meGpio_Init_(WIZNET_CS);
  meGpio_Set_(WIZNET_CS);
  
  WIZNET_RST->u_dir = eGPIO_DIR_OUTPUT;
  WIZNET_RST->u_out_type = eGPIO_PUSH_PULL;
  meGpio_Init_(WIZNET_RST);
  meGpio_Set_(WIZNET_RST);

  WIZNET_SPI->u_role = eSPI_ROLE_MASTER;
  WIZNET_SPI->u_bit_order = eSPI_FIRSTBIT_MSB;
  WIZNET_SPI->u_data_size = 8;
  WIZNET_SPI->u_mode = eSPI_MODE_3;
  meSpi_Init_(WIZNET_SPI);
  
  meCONSOLE_ADD_GROUP_(wiz610io, NULL, "CDRV/WIZ610io");
  
  reg_wizchip_cs_cbfunc(W6100_Select, W6100_Unselect);
  reg_wizchip_spi_cbfunc(W6100_ReadByte, W6100_WriteByte, W6100_ReadBuff, W6100_WriteBuff);
  reg_wizchip_cris_cbfunc(W6100_cris_en, W6100_cris_ex);

  uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
  wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);
  
  wiz_NetInfo net_info = {
    .mac  = { 0xEA, 0x11, 0x22, 0x33, 0x44, 0xEA },
    .ip  = { 192, 168, 1, 226 },
    .sn = { 255, 255, 255, 0 },
    .gw = { 192, 168, 1, 251 },
    .dns = { 0, 0, 0, 0 },
    .lla = { 0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,0x08, 0xDC,0xFF, 0xFE,0x57, 0x57,0x25 },
    .gua = { 0x20, 0x01, 0x02, 0xB8, 0x00, 0x10, 0x00, 0x01, 0x02, 0x08, 0xDC, 0xFF, 0xFE, 0x57, 0x57, 0x25 },
    .sn6 = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    .gw6={ 0xFE, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x87, 0xFF, 0xFE, 0x08, 0x4C, 0x81 }
  };
  
  wizchip_setnetinfo(&net_info);
  
	return 0;
}

/*
===============================================================================
            ##### wiz610io_initialize_example.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 */
static void W6100_Select(void) {
  meGpio_Reset_(WIZNET_CS);
}

/**
 * @brief 
 * 
 */
static void W6100_Unselect(void) {
  meGpio_Set_(WIZNET_CS);
}

/**
 * @brief 
 * 
 * @param buff 
 * @param len 
 */
static void W6100_ReadBuff(uint8_t* buff, short len) {
  meSpi_Receive_(WIZNET_SPI, buff, len, 1000);
}

/**
 * @brief 
 * 
 * @param buff 
 * @param len 
 */
static void W6100_WriteBuff(uint8_t* buff, short len) {
    meSpi_Transmit_(WIZNET_SPI, buff, len, 1000);
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
static uint8_t W6100_ReadByte(void) {
    uint8_t byte;
    W6100_ReadBuff(&byte, sizeof(byte));
    return byte;
}

/**
 * @brief 
 * 
 * @param byte 
 */
static void W6100_WriteByte(uint8_t byte) {
    W6100_WriteBuff(&byte, sizeof(byte));
}

/**
 * @brief 
 * 
 */
static void W6100_cris_en(void) {
  __disable_irq();
}

/**
 * @brief 
 * 
 */
static void W6100_cris_ex(void) {
  __enable_irq();
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

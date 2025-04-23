/**
 ******************************************************************************
 *  @file 			wiz850io_initialize_example.c
 *  @brief 			
 *  @details 		
 *  @author 		Adel Ghaderan
 *  @version 		1.0.0
 *  @date 			1396/05/03
 *  @pre 				
 *  @bug 				
 *  @warning 		
 *  @copyright 	GNU Public License.
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 ==============================================================================
                    ##### -------- features #####
 ==============================================================================         
 


									##### How to use -------- #####
 ==============================================================================  
 


 ******************************************************************************
 @verbatim
 @endverbatim
*/
 
/* Includes ------------------------------------------------------------------*/
#include "hal\port\stm32f4xx\inc\me_hal.h"

#include "w5500.h"
#include "wiz850io_cmd.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WIZNET_SPI  me_hal.spi->spi3
#define WIZNET_CS   me_hal.gpio->PG2
#define WIZNET_RST  me_hal.gpio->PB0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void W5500_Select(void) {
  meGpio_Reset_(WIZNET_CS);
}

void W5500_Unselect(void) {
  meGpio_Set_(WIZNET_CS);
}

void W5500_ReadBuff(uint8_t* buff, uint16_t len) {
  meSpi_Receive_(WIZNET_SPI, buff, len, 1000);
}

void W5500_WriteBuff(uint8_t* buff, uint16_t len) {
    meSpi_Transmit_(WIZNET_SPI, buff, len, 1000);
}

uint8_t W5500_ReadByte(void) {
    uint8_t byte;
    W5500_ReadBuff(&byte, sizeof(byte));
    return byte;
}

void W5500_WriteByte(uint8_t byte) {
    W5500_WriteBuff(&byte, sizeof(byte));
}

void W5500_cris_en(void) {
  __disable_irq();
}

void W5500_cris_ex(void) {
  __enable_irq();
}

/*
===============================================================================
                       ##### ---------- functions #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t wiz850io_initialize(void) {
  
  WIZNET_CS->u_dir = eGPIO_DIR_OUTPUT;
  WIZNET_CS->u_out_type = eGPIO_PUSH_PULL;
  meGpio_Init_(WIZNET_CS);
  meGpio_Set_(WIZNET_CS);
  
  WIZNET_RST->u_dir = eGPIO_DIR_OUTPUT;
  WIZNET_RST->u_out_type = eGPIO_PUSH_PULL;
  meGpio_Init_(WIZNET_RST);
  meGpio_Set_(WIZNET_RST);
  
  WIZNET_SPI->u_role = eSPI_ROLE_MASTER;
  WIZNET_SPI->u_mode = eSPI_MODE_3;
  WIZNET_SPI->u_data_size = eSPI_DATA_SIZE_8BIT;
  meSpi_Init_(WIZNET_SPI);
  
  meCONSOLE_ADD_GROUP_(wiz850io, NULL, true, 2, "BSP", "WIZ850IO");
  
  reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
  reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
  reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);
  reg_wizchip_cris_cbfunc(W5500_cris_en, W5500_cris_ex);

  uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
  wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);
  
  wiz_NetInfo net_info = {
    .mac  = { 0xEA, 0x11, 0x22, 0x33, 0x44, 0xEA },
    .ip  = { 192, 168, 1, 226 },
    .sn = { 255, 255, 255, 0 },
    .gw = { 192, 168, 1, 251 },
    .dns = { 0, 0, 0, 0 },
    .dhcp = NETINFO_STATIC
  };
  
  wizchip_setnetinfo(&net_info);
  
	return 0;
}

/**End of Group_Name
  * @}
  */

/********************************* END OF FILE ********************************/

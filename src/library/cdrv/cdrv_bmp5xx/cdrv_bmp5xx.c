/**
******************************************************************************
* @file           : cdrv_bmp5xx.c
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
#include "cdrv_bmp5xx.h"

#include "bmp5.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static int8_t Bmp5Read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr);
static int8_t Bmp5Write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len, void *intf_ptr);
static void Bmp5DelayUs(uint32_t period, void *intf_ptr);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_bmp5xx.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvBmp5xx_Init(sCdrvBmp5xxObj * const me) {
  me->_init = false;
	
	if(me->ChipSelect == NULL) {
		return 1;
	}
	if(me->Spi == NULL) {
		return 1;
	}
	
	me->ChipSelect->u_dir = eGPIO_DIR_OUTPUT;
	me->ChipSelect->u_out_type = eGPIO_PUSH_PULL;
	if(meGpio_Init_(me->ChipSelect) != 0) {
		return 1;
	}
	meGpio_Set_(me->ChipSelect);
	
	if(me->Interrupt != NULL) {
		me->Interrupt->u_dir = eGPIO_DIR_INPUT;
		me->Interrupt->u_in_type = eGPIO_PULL_NONE;
		if(meGpio_Init_(me->Interrupt) != 0) {
			return 1;
		}
	}
	
	me->Spi->u_role = eSPI_ROLE_MASTER;
	me->Spi->u_mode = eSPI_MODE_0;
	me->Spi->u_bit_order = eSPI_FIRSTBIT_MSB;
	me->Spi->u_data_size = 8;
	if(meSpi_Init_(me->Spi) != 0) {
		return 1;
	}

  me->_bmp5xxDevice.intf = BMP5_SPI_INTF;
	me->_bmp5xxDevice.read = Bmp5Read;
	me->_bmp5xxDevice.write = Bmp5Write;
	me->_bmp5xxDevice.delay_us = Bmp5DelayUs;
	me->_bmp5xxDevice.intf_ptr = (void*)me;
	

  me->_init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvBmp5xx_InitChip(sCdrvBmp5xxObj * const me) {
	
	if(!me->_init) {
		return 1;
	}
	
	if(bmp5_soft_reset(&me->_bmp5xxDevice) != 0) {
		return 1;
	}
	
	if(bmp5_init(&me->_bmp5xxDevice) != 0) {
		return 1;
	}
	
	return 0;
}

/*
===============================================================================
                  ##### cdrv_bmp5xx.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param reg_addr 
 * @param read_data 
 * @param len 
 * @param intf_ptr 
 * @return int8_t 
 */
static int8_t Bmp5Read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr) {
	sCdrvBmp5xxObj *intf = (sCdrvBmp5xxObj*)intf_ptr;
	
	meGpio_Reset_(intf->ChipSelect);
	int8_t ret = meSpi_Transmit_(intf->Spi, &reg_addr, 1, intf->SpiTimeout);
	ret |= meSpi_Receive_(intf->Spi, read_data, len, intf->SpiTimeout);
	meGpio_Set_(intf->ChipSelect);
	
	return ret;
}

/**
 * @brief 
 * 
 * @param reg_addr 
 * @param read_data 
 * @param len 
 * @param intf_ptr 
 * @return int8_t 
 */
static int8_t Bmp5Write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len, void *intf_ptr) {
	sCdrvBmp5xxObj *intf = (sCdrvBmp5xxObj*)intf_ptr;
	
	meGpio_Reset_(intf->ChipSelect);
	int8_t ret = meSpi_Transmit_(intf->Spi, &reg_addr, 1, intf->SpiTimeout);
	ret |= meSpi_Transmit_(intf->Spi, (uint8_t*)read_data, len, intf->SpiTimeout);
	meGpio_Set_(intf->ChipSelect);
	
	return ret;
}

/**
 * @brief 
 * 
 * @param period 
 * @param intf_ptr 
 */
static void Bmp5DelayUs(uint32_t period, void *intf_ptr) {
	meDelay_us_(period);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

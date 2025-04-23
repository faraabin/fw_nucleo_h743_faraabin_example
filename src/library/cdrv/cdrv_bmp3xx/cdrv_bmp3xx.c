/**
******************************************************************************
* @file           : cdrv_bmp3xx.c
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
#include "cdrv_bmp3xx.h"

#include "bmp3.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static int8_t Bmp3Read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr);
static int8_t Bmp3Write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len, void *intf_ptr);
static void Bmp3DelayUs(uint32_t period, void *intf_ptr);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_bmp3xx.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvBmp3xx_Init(sCdrvBmp3xxObj * const me) {
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

  me->_bmp3xxDevice.intf = BMP3_SPI_INTF;
	me->_bmp3xxDevice.read = Bmp3Read;
	me->_bmp3xxDevice.write = Bmp3Write;
	me->_bmp3xxDevice.delay_us = Bmp3DelayUs;
	me->_bmp3xxDevice.intf_ptr = (void*)me;
	if(bmp3_init(&me->_bmp3xxDevice) != 0) {
		return 1;
	}

  me->_init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvBmp3xx_InitChip(sCdrvBmp3xxObj * const me) {
	
	if(!me->_init) {
		return 1;
	}
	
	if(bmp3_soft_reset(&me->_bmp3xxDevice) != 0) {
		return 1;
	}
	
	if(bmp3_init(&me->_bmp3xxDevice) != 0) {
		return 1;
	}
	
	return 0;
}

/*
===============================================================================
                  ##### cdrv_bmp3xx.c Private Functions #####
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
static int8_t Bmp3Read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr) {
	sCdrvBmp3xxObj *intf = (sCdrvBmp3xxObj*)intf_ptr;
	
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
static int8_t Bmp3Write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len, void *intf_ptr) {
	sCdrvBmp3xxObj *intf = (sCdrvBmp3xxObj*)intf_ptr;
	
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
static void Bmp3DelayUs(uint32_t period, void *intf_ptr) {
	meDelay_us_(period);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

/**
******************************************************************************
* @file           : cdrv_ads79xx.c
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
#include "cdrv_ads79xx.h"

#include "library\chrono\me_chrono.h"

/* Private define ------------------------------------------------------------*/
#define SPI_TIMEOUT_ms      10
#define FRAME_HOLD_TIME_ms  10

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint16_t Read(TysCdrvAds79xx_Obj *me, uint16_t data);
static void Write(TysCdrvAds79xx_Obj *me, uint16_t data);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_ads79xx.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t CdrvAds79xx_Init(TysCdrvAds79xx_Obj * const me) {
  me->init = false;
  uint16_t data;

  if((me->u_cs == NULL) || (me->u_spi == NULL)) {
    return 1;
  }
	
	me->u_cs->u_dir = eGPIO_DIR_OUTPUT;
	me->u_cs->u_out_type = eGPIO_PUSH_PULL;
	meGpio_Init_(me->u_cs);
	meGpio_Set_(me->u_cs);
	
	me->u_spi->u_bit_order = eSPI_FIRSTBIT_MSB;
	me->u_spi->u_data_size = 8;
	me->u_spi->u_mode = eSPI_MODE_0;
	me->u_spi->u_role = eSPI_ROLE_MASTER;
	meSpi_Init_(me->u_spi);

  switch (me->u_mode)
  {
  case eADS79_MODE_MANUAL:
    data = 0x0000;
    //Request for manual mode
    data |= (1 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Entry into manual mode
    data |= (1 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Operation in manual mode
    data |= (1 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    break;
  
  case eADS79_MODE_AUTO1:
    data = 0x0000;
    //Entry into auto-1 register programming sequence
    data |= (8 << 12);
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Auto-1 register programming to select active channels
    data = 0xFFFF; //TODO: Extend library to enable user selected channels
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    data = 0x0000;
    //Request for auto-1 mode
    data |= (2 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Entry into auto-1 mode
    data |= (2 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Operation in auto-1 mode
    data |= (2 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    break;

  case eADS79_MODE_AUTO2:
    data = 0x0000;
    //Auto-2 register programming
    data |= (9 << 12);
    data |= (0xF << 6); //TODO: Extend library to enable user selected channels
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    data = 0x0000;
    //Request for auto-1 mode
    data |= (3 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Entry into auto-1 mode
    data |= (3 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    //Operation in auto-1 mode
    data |= (3 << 12); //Selects manual mode
    data |= (1 << 11); //Enables programming of range
    data |= (0 << 7);  //Binary address of channel
    data |= (me->u_range == eADS79_RANGE1) ? (0 << 6) : (1 << 6); //Selects range for channel
    data |= (0 << 5);  //No power down
    data |= (0 << 4);
    data |= (0 << 0);  //TODO: Extend library to work with device GPIOs
    Write(me, data);

    meDelay_ms_(FRAME_HOLD_TIME_ms);

    break;

  default:
    return 1;
  }

  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
void CdrvAds79xx_Update(TysCdrvAds79xx_Obj * const me) {
	if(!me->init) {
		return;
	}
	uint16_t data;
	
	switch (me->u_mode)
  {
  case eADS79_MODE_MANUAL:
    data = 0x0000;
    me->manual_channel_counter = (me->manual_channel_counter + 1) % 16;
    data |= (1 << 12);
    data |= (me->manual_channel_counter << 7);
		break;

  case eADS79_MODE_AUTO1:
  case eADS79_MODE_AUTO2:
    data = 0x0000; //Continued operation in selected mode
    break;
  
  default:
    return;
  }
	
	Read(me, data);
	uint8_t channel_number = me->read_value >> me->u_adc_bits;
	uint16_t channel_value = me->read_value & ((uint16_t)(1 << me->u_adc_bits) - 1);
	me->value_array[channel_number] = channel_value;
	
	me->u_raw_value.ch0 = me->value_array[0];
	me->u_raw_value.ch1 = me->value_array[1];
	me->u_raw_value.ch2 = me->value_array[2];
	me->u_raw_value.ch3 = me->value_array[3];
	me->u_raw_value.ch4 = me->value_array[4];
	me->u_raw_value.ch5 = me->value_array[5];
	me->u_raw_value.ch6 = me->value_array[6];
	me->u_raw_value.ch7 = me->value_array[7];
	me->u_raw_value.ch8 = me->value_array[8];
	me->u_raw_value.ch9 = me->value_array[9];
	me->u_raw_value.ch10 = me->value_array[10];
	me->u_raw_value.ch11 = me->value_array[11];
	me->u_raw_value.ch12 = me->value_array[12];
	me->u_raw_value.ch13 = me->value_array[13];
	me->u_raw_value.ch14 = me->value_array[14];
	me->u_raw_value.ch15 = me->value_array[15];
}

/*
===============================================================================
                    ##### cdrv_ads79xx.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint16_t 
 */
static uint16_t Read(TysCdrvAds79xx_Obj *me, uint16_t data) {
	uint8_t tx_buffer[2];
	uint8_t rx_buffer[2];
	
	tx_buffer[0] = data >> 0x08;
	tx_buffer[1] = data & 0xFF;
	meGpio_Reset_(me->u_cs);
	if(meSpi_TransmitReceive_(me->u_spi, tx_buffer, rx_buffer, sizeof(tx_buffer), SPI_TIMEOUT_ms) != 0) {
		meGpio_Set_(me->u_cs);
		return 0;
	}
	meGpio_Set_(me->u_cs);
	
	me->read_value = (uint16_t)(rx_buffer[0] << 0x08) | (uint16_t)(rx_buffer[1]);
	
	return me->read_value;
}

/**
 * @brief 
 * 
 * @param me 
 * @param data 
 */
static void Write(TysCdrvAds79xx_Obj *me, uint16_t data) {
	uint8_t tx_buffer[2];
	
	tx_buffer[0] = data >> 0x08;
	tx_buffer[1] = data & 0xFF;
	
  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, tx_buffer, sizeof(tx_buffer), SPI_TIMEOUT_ms);
  meGpio_Set_(me->u_cs);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

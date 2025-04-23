/**
 ******************************************************************************
 *  @file         cdrv_as5048a.c
 *  @brief        ...
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 * DESCRIPTION:
 *
 ******************************************************************************
 * HOW TO USE:
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "cdrv_as5048a.h"

#include <stdlib.h>

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AS5048A_CLEAR_ERROR_FLAG            0x0001
#define AS5048A_PROGRAMMING_CONTROL         0x0003
#define AS5048A_OTP_REGISTER_ZERO_POS_HIGH  0x0016
#define AS5048A_OTP_REGISTER_ZERO_POS_LOW   0x0017
#define AS5048A_DIAG_AGC                    0x3FFD
#define AS5048A_MAGNITUDE                   0x3FFE
#define AS5048A_ANGLE                       0x3FFF

#define AS5048A_AGC_FLAG                    0xFF
#define AS5048A_ERROR_PARITY_FLAG           0x04
#define AS5048A_ERROR_COMMAND_INVALID_FLAG  0x02
#define AS5048A_ERROR_FRAMING_FLAG          0x01

#define AS5048A_DIAG_COMP_HIGH              0x2000
#define AS5048A_DIAG_COMP_LOW               0x1000
#define AS5048A_DIAG_COF                    0x0800
#define AS5048A_DIAG_OCF                    0x0400

#define AS5048A_MAX_VALUE                   8191.0f

#define PI                                  3.14159265359f

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t CalcEvenParity(uint16_t);
static uint16_t ReadRegister(TysCdrvAs5048a_Obj * const me, uint16_t addr);
static uint16_t WriteRegister(TysCdrvAs5048a_Obj * const me, uint16_t addr, uint16_t data);
static uint16_t GetState(TysCdrvAs5048a_Obj * const me);
static uint8_t GetGain(TysCdrvAs5048a_Obj * const me);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvAs5048a_Init(TysCdrvAs5048a_Obj * const me) {
  me->init = false;
  
  if((me->u_spi == NULL) || (me->u_cs == NULL)) {
    return 1;
  }
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvAs5048a_GetRawRotation(TysCdrvAs5048a_Obj * const me, uint16_t *value) {
  
  *value = ReadRegister(me, AS5048A_ANGLE);
  
  return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvAs5048a_GetRotation(TysCdrvAs5048a_Obj * const me, int16_t *value) {
  
  uint16_t data;
	int16_t rotation;

	if(CdrvAs5048a_GetRawRotation(me, &data) != 0) {
    return 1;
  }
  
	rotation = (int16_t)(data) - (int16_t)(me->u_position);
	if(rotation > AS5048A_MAX_VALUE) { 
		rotation = -((0x3FFF) - rotation); //more than -180
  }

  *value = rotation;
  
	return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvAs5048a_GetRotationInDegrees(TysCdrvAs5048a_Obj * const me, float *value) {
  
  int16_t rotation;

//  if(CdrvAs5048a_GetRotation(me, &rotation) != 0) {
//    return 1;
//  }
//  
//	*value = 360.0 * (rotation + AS5048A_MAX_VALUE) / (AS5048A_MAX_VALUE * 2.0);
  
  uint16_t tmp;
  
  if(CdrvAs5048a_GetRawRotation(me, &tmp) != 0) {
    return 1;
  }
  
	*value = 360.0f * (tmp) / (AS5048A_MAX_VALUE * 2.0f);
  
	return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t CdrvAs5048a_GetRotationInRadians(TysCdrvAs5048a_Obj * const me, double *value) {
  
  int16_t rotation;

  if(CdrvAs5048a_GetRotation(me, &rotation) != 0) {
    return 1;
  }
  
	*value = PI * (rotation + AS5048A_MAX_VALUE) / AS5048A_MAX_VALUE;
  
	return 0;
}

/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t CalcEvenParity(uint16_t value) {
	uint8_t cnt = 0;

	for (uint8_t i = 0; i < 16; i++) {
		if (value & 0x1) {
			cnt++;
		}
		value >>= 1;
	}
  
	return cnt & 0x1;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint16_t ReadRegister(TysCdrvAs5048a_Obj * const me, uint16_t addr) {
  
	uint16_t command = 0x4000; // PAR=0 R/W=R
	command = command | addr;

	//Add a parity bit on the the MSB
	command |= (uint16_t)(CalcEvenParity(command) << 0xF);
  
  uint8_t tmp_tx[2];
  uint8_t tmp_rx[2];
  
  tmp_tx[0] = command >> 8;
  tmp_tx[1] = command;
  
  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, tmp_tx, 2, 10000);
  meGpio_Set_(me->u_cs);
  
  meDelay_us_(10);
  
  tmp_tx[0] = 0x00;
  tmp_tx[1] = 0x00;
  
  meGpio_Reset_(me->u_cs);
  meSpi_TransmitReceive_(me->u_spi, tmp_tx, tmp_rx, 2, 10000);
  meGpio_Set_(me->u_cs);
  
  uint16_t response = ((uint16_t)tmp_rx[0] << 8) | tmp_rx[1];
  
	//Check if the error bit is set
	if (response & 0x4000) {
		me->errorFlag = true;
	} else {
		me->errorFlag = false;
	}

	//Return the data, stripping the parity and error bits
	return response & ~0xC000;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint16_t WriteRegister(TysCdrvAs5048a_Obj * const me, uint16_t addr, uint16_t data) {

	uint16_t command = 0x0000; // PAR=0 R/W=W
	command |= addr;

	//Add a parity bit on the the MSB
	command |= (uint16_t)(CalcEvenParity(command) << 0xF);

  uint8_t tmp_tx[2];
  uint8_t tmp_rx[2];
  
  tmp_tx[0] = command >> 8;
  tmp_tx[1] = command;

  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, tmp_tx, 2, 10000);
  meGpio_Set_(me->u_cs);
  
	uint16_t dataToSend = 0x0000;
	dataToSend |= data;

	//Craft another packet including the data and parity
	dataToSend |= (uint16_t)(CalcEvenParity(dataToSend) << 0xF);

	tmp_tx[0] = dataToSend >> 8;
  tmp_tx[1] = dataToSend;

  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, tmp_tx, 2, 10000);
  meGpio_Set_(me->u_cs);

  meDelay_us_(100);
	
  tmp_tx[0] = 0;
  tmp_tx[1] = 0;
  
  meGpio_Reset_(me->u_cs);
  meSpi_TransmitReceive_(me->u_spi, tmp_tx, tmp_rx, 2, 10000);
  meGpio_Set_(me->u_cs);
  
	uint16_t response = ((uint16_t)tmp_rx[0] << 8) | tmp_rx[1];

	//Return the data, stripping the parity and error bits
	return response & ~0xC000;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint16_t GetState(TysCdrvAs5048a_Obj * const me) {
  
	return ReadRegister(me, AS5048A_DIAG_AGC);
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
static uint8_t GetGain(TysCdrvAs5048a_Obj * const me) {
  
	uint16_t data = GetState(me);
	return (uint8_t)(data & AS5048A_AGC_FLAG);
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

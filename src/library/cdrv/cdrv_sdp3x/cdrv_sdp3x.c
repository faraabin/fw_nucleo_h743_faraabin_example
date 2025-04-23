/**
******************************************************************************
* @file           : cdrv_sdp3x.c
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
#include "cdrv_sdp3x.h"

/* Private define ------------------------------------------------------------*/
#define SDP3X_CLOCK_STRETCH_DELAY_ms	45

/* Private macro -------------------------------------------------------------*/
#define CheckInit_(ret_)	\
if(me->_init == false) {\
	return ret_;\
}

/* Private typedef -----------------------------------------------------------*/
// Sensor Commands
typedef enum {
  eCMD_UNDEFINED									= 0x0000,
  
	eCMD_START_CONTMEAS_MF_AVERAGE	= 0x3603,
  eCMD_START_CONTMEAS_MF_NONE			= 0x3608,
  eCMD_START_CONTMEAS_DP_AVERAGE	= 0x3615,
  eCMD_START_CONTMEAS_DP_NONE			= 0x361E,
  eCMD_STOP_CONTMEAS							= 0x3FF9,
	
	eCMD_TRIGMEAS_MF_POLLING				= 0x3624,
	eCMD_TRIGMEAS_MF_CLK_STRETCH		= 0x3726,
	eCMD_TRIGMEAS_DP_POLLING				= 0x362F,
	eCMD_TRIGMEAS_DP_CLK_STRETCH		= 0x372D,
	
	eCMD_SOFT_RESET									= 0x0006,
	
	eCMD_ENTER_SLEEP_MODE						= 0x3677,
	
	eCMD_READ_PID1									= 0x367C,
	eCMD_READ_PID2									= 0xE102
	
}eSdp3xCmd;

/* Private variables ---------------------------------------------------------*/
static const float scaleFactorTemperature = 200.0f;

/* Private function prototypes -----------------------------------------------*/
static uint8_t WriteCommand(sCdrvSdp3xObj * const me, uint8_t addr, uint16_t command);
static uint8_t ReadWordAndVerify(sCdrvSdp3xObj * const me, uint8_t addr, uint16_t *data);

static uint8_t CalculateCrc(uint16_t data);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_sdp3x.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param i2cAddr 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_Init(sCdrvSdp3xObj * const me, uint8_t i2cAddr) {
	me->_init = false;
	if(me->I2c == NULL) {
		return 1;
	}
	
	if(me->Irqn != NULL) {
		me->Irqn->u_dir = eGPIO_DIR_INPUT;
		me->Irqn->u_in_type = eGPIO_PULL_NONE;
		if(meGpio_Init_(me->Irqn) != 0) {
			return 1;
		}
	}
	
  me->I2cAddress = i2cAddr;
	if(meI2c_Init_(me->I2c) != 0) {
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
uint8_t fCdrvSdp3x_ReadProductId(sCdrvSdp3xObj * const me) {
	CheckInit_(1);
	Tyu_4Byte productNumber;
	Tyu_8Byte serialNumber;
	
	if(WriteCommand(me, me->I2cAddress, eCMD_READ_PID1) != 0) {
		return 1;
	}
	if(WriteCommand(me, me->I2cAddress, eCMD_READ_PID2) != 0) {
		return 1;
	}
	
	if(ReadWordAndVerify(me, me->I2cAddress, &productNumber.u16[1]) != 0) {
		return 1;
	}
	if(ReadWordAndVerify(me, me->I2cAddress, &productNumber.u16[0]) != 0) {
		return 1;
	}
	
	if(ReadWordAndVerify(me, me->I2cAddress, &serialNumber.u16[3]) != 0) {
		return 1;
	}
	if(ReadWordAndVerify(me, me->I2cAddress, &serialNumber.u16[2]) != 0) {
		return 1;
	}
	if(ReadWordAndVerify(me, me->I2cAddress, &serialNumber.u16[1]) != 0) {
		return 1;
	}
	if(ReadWordAndVerify(me, me->I2cAddress, &serialNumber.u16[0]) != 0) {
		return 1;
	}
	
	me->DevProductNumber = productNumber.u32;
	me->DevSerialNumber = serialNumber.u64;
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_StartContinousMeasurement(sCdrvSdp3xObj * const me, eCdrvSdp3xTempComp tempConfig, eCdrvSdp3xAveraging avgConfig) {
	CheckInit_(1);
	
	if((tempConfig == eSDP3X_TEMPCOMP_MASS_FLOW) && (avgConfig == eSDP3X_AVERAGING_NONE)) {
		if(WriteCommand(me, me->I2cAddress, eCMD_START_CONTMEAS_MF_NONE) != 0) {
			return 1;
		}
	} else if((tempConfig == eSDP3X_TEMPCOMP_MASS_FLOW) && (avgConfig == eSDP3X_AVERAGING_TILL_READ)) {
		if(WriteCommand(me, me->I2cAddress, eCMD_START_CONTMEAS_MF_AVERAGE) != 0) {
			return 1;
		}
	} else if((tempConfig == eSDP3X_TEMPCOMP_DIFFERNTIAL_PRESSURE) && (avgConfig == eSDP3X_AVERAGING_NONE)) {
		if(WriteCommand(me, me->I2cAddress, eCMD_START_CONTMEAS_DP_NONE) != 0) {
			return 1;
		}
	} else if((tempConfig == eSDP3X_TEMPCOMP_DIFFERNTIAL_PRESSURE) && (avgConfig == eSDP3X_AVERAGING_TILL_READ)) {
		if(WriteCommand(me, me->I2cAddress, eCMD_START_CONTMEAS_DP_AVERAGE) != 0) {
			return 1;
		}
	}
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_StopContinousMeasurement(sCdrvSdp3xObj * const me) {
	CheckInit_(1);
	
	if(WriteCommand(me, me->I2cAddress, eCMD_STOP_CONTMEAS) != 0) {
		return 1;
	}
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_TriggerMeasurement(sCdrvSdp3xObj * const me, eCdrvSdp3xData trigMode) {
	CheckInit_(1);
	
	if(trigMode == eTRIG_DIFF_PRESSURE) {
		if(WriteCommand(me, me->I2cAddress, eCMD_TRIGMEAS_DP_POLLING) != 0) {
			return 1;
		}
	} else if(trigMode == eTRIG_MASS_FLOW) {
		if(WriteCommand(me, me->I2cAddress, eCMD_TRIGMEAS_MF_POLLING) != 0) {
			return 1;
		}
	}
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_ReadMeasurementResults(sCdrvSdp3xObj * const me) {
	CheckInit_(1);
	uint16_t diffPressureRaw;
	uint16_t diffPressureScaleFactor;
	uint16_t temperatureRaw;
	
	if(ReadWordAndVerify(me, me->I2cAddress, &diffPressureRaw) != 0) {
		return 1;
	}
	if(ReadWordAndVerify(me, me->I2cAddress, &temperatureRaw) != 0) {
		return 1;
	}
	if(ReadWordAndVerify(me, me->I2cAddress, &diffPressureScaleFactor) != 0) {
		return 1;
	}
	
	me->Temperature = (float)temperatureRaw / scaleFactorTemperature;
	me->DiffPressure = (float)diffPressureRaw / (float)(diffPressureScaleFactor);
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_SoftwareReset(sCdrvSdp3xObj * const me) {
	CheckInit_(1);
	
	if(WriteCommand(me, me->I2cAddress, eCMD_SOFT_RESET) != 0) {
		return 1;
	}
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_EnterSleepMode(sCdrvSdp3xObj * const me) {
	CheckInit_(1);
	
	if(WriteCommand(me, me->I2cAddress, eCMD_ENTER_SLEEP_MODE) != 0) {
		return 1;
	}
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvSdp3x_ExitSleepMode(sCdrvSdp3xObj * const me) {
	CheckInit_(1);
	
	if(fCdrvSdp3x_ReadMeasurementResults(me) != 0) {
		return 1;
	}
	
	return 0;
}

/*
===============================================================================
                  ##### cdrv_sdp3x.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @param command 
 * @return uint8_t 
 */
static uint8_t WriteCommand(sCdrvSdp3xObj * const me, uint8_t addr, uint16_t command) {
	uint8_t cmdBuffer[2];
	
	cmdBuffer[0] = (command >> 8) & 0xFF;
	cmdBuffer[1] = (command >> 0) & 0xFF;
	
	return meI2c_Transmit_(me->I2c, ((addr << 1) | 0x00), cmdBuffer, 2, 100);
}

/**
 * @brief 
 * 
 * @param me 
 * @param addr 
 * @param data 
 * @return uint8_t 
 */
static uint8_t ReadWordAndVerify(sCdrvSdp3xObj * const me, uint8_t addr, uint16_t *data) {
	uint8_t readBuffer[3];
	
	if(meI2c_Receive_(me->I2c, ((addr << 1) | 0x01), readBuffer, 3, 100) != 0) {
		return 1;
	}
	
	uint16_t data2check = (uint16_t)(((uint16_t)readBuffer[0] << 8) | (readBuffer[1]));
	uint8_t rxCrc = readBuffer[2];
	
	if(rxCrc != CalculateCrc(data2check)) {
		return 1;
	}
	*data = data2check;
	
	return 0;
}

/**
 * @brief 
 * 
 * @param data 
 * @return uint8_t 
 */
static uint8_t CalculateCrc(uint16_t data) {
	uint8_t crc = 0xFF;
	
	// calculates 8-Bit checksum with given polynomial 0x31 (x^8 + x^5 + x^4 + 1)
	crc ^= (uint8_t)((data >> 8) & 0xFF);
	crc ^= (uint8_t)((data >> 0) & 0xFF);
	
	for(int bit = 8; bit > 0; --bit) {
		if(crc & 0x80) {
			crc = (crc << 1) ^ 0x31;
		} else {
			crc = (crc << 1);
		}
	}
	
	return crc;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

/**
******************************************************************************
* @file           : cdrv_icm20948.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2024 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2024 FaraabinCo.
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
#include "cdrv_icm20948.h"

#include "library\core\me_type_tool.h"

/* Private define ------------------------------------------------------------*/
#define WRITE_BIT (0)
#define READ_BIT  (1)
#define DEV_ADDR	(0xD0)

#define ICM20948_ADDR_WHO_AM_I			0x00
#define ICM20948_ADDR_PWR_MGMT_1		0x06
#define ICM20948_ADDR_PWR_MGMT_2		0x07
#define ICM20948_ADDR_ACCEL_XOUT_H	0x2D
#define ICM20948_ADDR_ACCEL_XOUT_L	0x2E
#define ICM20948_ADDR_ACCEL_YOUT_H	0x2F
#define ICM20948_ADDR_ACCEL_YOUT_L	0x30
#define ICM20948_ADDR_ACCEL_ZOUT_H	0x31
#define ICM20948_ADDR_ACCEL_ZOUT_L	0x32
#define ICM20948_ADDR_GYRO_XOUT_H		0x33
#define ICM20948_ADDR_GYRO_XOUT_L		0x34
#define ICM20948_ADDR_GYRO_YOUT_H		0x35
#define ICM20948_ADDR_GYRO_YOUT_L		0x36
#define ICM20948_ADDR_GYRO_ZOUT_H		0x37
#define ICM20948_ADDR_GYRO_ZOUT_L		0x38
#define ICM20948_ADDR_REG_BANK_SEL	0x7F

#define ICM20948_WHO_AM_I_DEFAULT           (0xEA)
#define ICM20948_EXT_SLV_SENS_DATA_COUNT    (25)

#define ICM20948_GYRO_RATE_250              (0x00)
#define ICM20948_GYRO_LPF_17HZ              (0x29)

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t I2cRead(sCdrvIcm20948Obj * const me, uint8_t regAddress, uint8_t *buffer, uint16_t size);
static uint8_t I2cWriteByte(sCdrvIcm20948Obj * const me, uint8_t regAddress, uint8_t value);
static void SelectRegisterBank(sCdrvIcm20948Obj * const me, uint8_t bankNo);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
								##### cdrv_icm20948.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param ad0State 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_Init(sCdrvIcm20948Obj * const me, uint8_t ad0State) {
	
	me->_init = false;
	
	if(me->I2c == NULL) {
		return 1;
	}
	
	if(meI2c_Init_(me->I2c) != 0) {
    return 1;
  }
	me->_devAddr = DEV_ADDR + ad0State;
	
	fCdrvIcm20948_Reset(me);
	meDelay_ms_(100);
	
	if(fCdrvIcm20948_ReadId(me) != ICM20948_WHO_AM_I_DEFAULT) {
		return 1;
	}
	
	I2cWriteByte(me, ICM20948_ADDR_PWR_MGMT_1, 0x01); //Turn on the device
	
	fCdrvIcm20948_SetGyroCfg(me, eGYRO_CFG_250DPS, eGYRO_CFG_LPF_0, 1);
	fCdrvIcm20948_SetAcclCfg(me, eACL_CFG_8G, eACL_CFG_LPF_0, 1);
	
	me->_init = true;
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_ReadId(sCdrvIcm20948Obj * const me) {
	uint8_t rxBuff = 0;
	
	SelectRegisterBank(me, 0x00);
	if(I2cRead(me, ICM20948_ADDR_WHO_AM_I, &rxBuff, 1) != 0) {
		return 0;
	}
	
	return rxBuff;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_Reset(sCdrvIcm20948Obj * const me) {
	
	SelectRegisterBank(me, 0x00);
	I2cWriteByte(me, ICM20948_ADDR_PWR_MGMT_1, 0x80);
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param fsCfg 
 * @param lpfCfg 
 * @param smplrtDiv 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_SetGyroCfg(sCdrvIcm20948Obj * const me, eCdrvIcm2094GyroFsCfg fsCfg, eCdrvIcm2094GyroLpfCfg lpfCfg, uint8_t smplrtDiv) {
	if(!me->_init) {
		return 1;
	}
	
	uint8_t gyroBuffer = 0x00;
	SelectRegisterBank(me, 0x02);
	
	if(lpfCfg != eGYRO_CFG_LPF_NONE) {
		
		gyroBuffer = (lpfCfg << 3) + (fsCfg << 1) + 1;
		me->_gyroFchoice = true;
		me->_gyroLpfCfg = lpfCfg;
		
	} else {
		
		gyroBuffer = (fsCfg << 1);
		me->_gyroFchoice = false;
		me->_gyroLpfCfg = eGYRO_CFG_LPF_NONE;
		
	}
	
	if(I2cWriteByte(me, 0x01, gyroBuffer) != 0) {
		return 1;
	}
	if(I2cWriteByte(me, 0x00, smplrtDiv) != 0) {
		return 1;
	}
	
	SelectRegisterBank(me, 0x00);
	
	me->_gyroFsCfg = fsCfg;
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_GetGyroData(sCdrvIcm20948Obj * const me) {
	if(!me->_init) {
		return 1;
	}
	
	uint8_t gyroBuffer[6] = {0x00};
	Tyu_2Byte gyroData;
	
//	SelectRegisterBank(me, 0x00);
	I2cRead(me, ICM20948_ADDR_GYRO_XOUT_H, gyroBuffer, sizeof(gyroBuffer));
	
	gyroData.byte[0] = gyroBuffer[1];
	gyroData.byte[1] = gyroBuffer[0];
	me->GyroX = gyroData.i16;
	gyroData.byte[0] = gyroBuffer[3];
	gyroData.byte[1] = gyroBuffer[2];
	me->GyroY = gyroData.i16;
	gyroData.byte[0] = gyroBuffer[5];
	gyroData.byte[1] = gyroBuffer[4];
	me->GyroZ = gyroData.i16;
	
	switch(me->_gyroFsCfg) {
		
		case eGYRO_CFG_250DPS: {
			me->GyroX /= 131.0f;
			me->GyroY /= 131.0f;
			me->GyroZ /= 131.0f;
			
			break;
		}
		
		case eGYRO_CFG_500DPS: {
			me->GyroX /= 65.5f;
			me->GyroY /= 65.5f;
			me->GyroZ /= 65.5f;
			
			break;
		}
		
		case eGYRO_CFG_1000DPS: {
			me->GyroX /= 32.8f;
			me->GyroY /= 32.8f;
			me->GyroZ /= 32.8f;
			
			break;
		}
		
		case eGYRO_CFG_2000DPS: {
			me->GyroX /= 16.4f;
			me->GyroY /= 16.4f;
			me->GyroZ /= 16.4f;
			
			break;
		}
		
		default: {
			me->GyroX  = 0.0f;
			me->GyroY  = 0.0f;
			me->GyroZ  = 0.0f;
			
			return 1;
		}
	}
	
	me->GyroX *= 0.0175427f;
	me->GyroY *= 0.0175427f;
	me->GyroZ *= 0.0175427f;
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param fsCfg 
 * @param lpfCfg 
 * @param smplrtDiv 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_SetAcclCfg(sCdrvIcm20948Obj * const me, eCdrvIcm2094AcclFsCfg fsCfg, eCdrvIcm2094AcclLpfCfg lpfCfg, uint16_t smplrtDiv) {
	if(!me->_init) {
		return 1;
	}
	
	uint8_t acclBuffer = 0x00;
	SelectRegisterBank(me, 0x02);
	
	if(lpfCfg != eACL_CFG_LPF_NONE) {
		
		acclBuffer = (lpfCfg << 3) + (fsCfg << 1) + 1;
		me->_acclFchoice = true;
		me->_acclLpfCfg = lpfCfg;
		
	} else {
		
		acclBuffer = (fsCfg << 1);
		me->_acclFchoice = false;
		me->_acclLpfCfg = eACL_CFG_LPF_NONE;
		
	}
	
	if(I2cWriteByte(me, 0x01, acclBuffer) != 0) {
		return 1;
	}
	if(I2cWriteByte(me, 0x10, ((smplrtDiv & 0xFFF) >> 8)) != 0) {
		return 1;
	}
	if(I2cWriteByte(me, 0x11, smplrtDiv & 0xFF) != 0) {
		return 1;
	}
	
	me->_acclFsCfg = fsCfg;
	
	SelectRegisterBank(me, 0x00);
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvIcm20948_GetAcclData(sCdrvIcm20948Obj * const me) {
	if(!me->_init) {
		return 1;
	}
	
	uint8_t acclBuffer[6] = {0x00};
	Tyu_2Byte acclData;
	
//	SelectRegisterBank(me, 0x00);
	I2cRead(me, ICM20948_ADDR_ACCEL_XOUT_H, acclBuffer, sizeof(acclBuffer));
	
	acclData.byte[0] = acclBuffer[1];
	acclData.byte[1] = acclBuffer[0];
	me->AcclX = acclData.i16;
	acclData.byte[0] = acclBuffer[3];
	acclData.byte[1] = acclBuffer[2];
	me->AcclY = acclData.i16;
	acclData.byte[0] = acclBuffer[5];
	acclData.byte[1] = acclBuffer[4];
	me->AcclZ = acclData.i16;
	
	switch(me->_acclFsCfg) {
		
		case eACL_CFG_2G: {
			
			me->AcclX /= 16384.0f;
			me->AcclY /= 16384.0f;
			me->AcclZ /= 16384.0f;
			
			
			break;
		}
		
		case eACL_CFG_4G: {
			
			me->AcclX /= 8192.0f;
			me->AcclY /= 8192.0f;
			me->AcclZ /= 8192.0f;
			
			break;
		}
		
		case eACL_CFG_8G: {
			
			me->AcclX /= 4096.0f;
			me->AcclY /= 4096.0f;
			me->AcclZ /= 4096.0f;
			
			break;
		}
		
		case eACL_CFG_16G: {
			
			me->AcclX /= 2048.0f;
			me->AcclY /= 2048.0f;
			me->AcclZ /= 2048.0f;
			
			break;
		}
		
		default: {
			
			me->AcclX = 0.0f;
			me->AcclY = 0.0f;
			me->AcclZ = 0.0f;
			
			return 1;
		}
	}
	
	me->AcclX *= 9.81f;
	me->AcclY *= 9.81f;
	me->AcclZ *= 9.81f;
	
	return 0;
}

/*
===============================================================================
								##### cdrv_icm20948.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param buffer 
 * @param size 
 * @return uint8_t 
 */
static uint8_t I2cRead(sCdrvIcm20948Obj * const me, uint8_t regAddress, uint8_t *buffer, uint16_t size) {
	
  uint8_t txByte = regAddress;

  if(meI2c_Transmit_(me->I2c, me->_devAddr + WRITE_BIT, &txByte, 1, 100) != 0) {
    return 1;
  }

  if(meI2c_Receive_(me->I2c, me->_devAddr + READ_BIT, buffer, size, 100) != 0) {
    return 1;
  }

  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @param buffer 
 * @param size 
 * @return uint8_t 
 */
static uint8_t I2cWriteByte(sCdrvIcm20948Obj * const me, uint8_t regAddress, uint8_t value) {
	uint8_t buffer[2] = {regAddress, value};
	
	return meI2c_Transmit_(me->I2c, me->_devAddr + WRITE_BIT, buffer, sizeof(buffer), 100);
}

/**
 * @brief 
 * 
 * @param me 
 * @param bankNo 
 */
static void SelectRegisterBank(sCdrvIcm20948Obj * const me, uint8_t bankNo) {
	if(bankNo > 3) {
		return;
	}
	
	I2cWriteByte(me, ICM20948_ADDR_REG_BANK_SEL, (bankNo << 4));
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

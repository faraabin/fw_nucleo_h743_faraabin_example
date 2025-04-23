/**
******************************************************************************
* @file           : cdrv_bmi160.c
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
#include "cdrv_bmi160.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### cdrv_bmi160.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 */
uint8_t fCdrvBmi160_Init(sCdrvBmi160Obj * const me, uint8_t ad0State) {
  
  me->_init = false;

  if(me->I2c == NULL) {
    return 1;
  }
  meI2c_Init_(me->I2c);
	
	me->_devAddress = BMI160_I2C_ADDR + ad0State;
  
	me->_device.id = me->_devAddress;
	me->_device.intf = BMI160_I2C_INTF;
	if(bmi160_init(&me->_device) != 0) {
		return 1;
	}
	
	me->_device.accel_cfg.odr = BMI160_ACCEL_ODR_800HZ;
	me->_device.accel_cfg.range = BMI160_ACCEL_RANGE_8G;
	me->_device.accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;
	me->_device.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
	me->_device.gyro_cfg.odr = BMI160_GYRO_ODR_800HZ;
	me->_device.gyro_cfg.range = BMI160_GYRO_RANGE_1000_DPS;
	me->_device.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;
	me->_device.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;
	if(bmi160_set_sens_conf(&me->_device) != 0) {
		return 1;
	}
  
  me->_init = true;
  return 0;
}

/*
===============================================================================
                    ##### cdrv_bmi160.c Private Functions #####
===============================================================================*/

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

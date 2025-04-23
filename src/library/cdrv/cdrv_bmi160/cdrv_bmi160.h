/**
******************************************************************************
* @file           : cdrv_bmi160.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_bmi160_H
#define __cdrv_bmi160_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\core\me_type.h"

#include "library\driver\intf\me_hal_i2c_intf.h"
#include "library\driver\intf\me_hal_gpio_intf.h"

#include "bmi160.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {

  bool _init;

  TysI2c_Obj *I2c;
	uint8_t _devAddress;
	
	struct bmi160_dev _device;
	
	struct bmi160_sensor_data Accel;
	struct bmi160_sensor_data Gyro;

}sCdrvBmi160Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvBmi160_Init(sCdrvBmi160Obj * const me, uint8_t ad0State);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_BMI160_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

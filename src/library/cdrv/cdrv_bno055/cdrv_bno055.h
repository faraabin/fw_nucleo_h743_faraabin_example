/**
******************************************************************************
* @file           : cdrv_bno055.h
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
#ifndef __cdrv_bno055_H
#define __cdrv_bno055_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\core\me_type.h"

#include "library\driver\intf\me_hal_i2c_intf.h"
#include "library\driver\intf\me_hal_gpio_intf.h"

#include "bno055.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {

  bool _init;

  TysGpio_Obj *Interrupt;
  TysGpio_Obj *Reset;
	TysGpio_Obj *Address;
  struct bno055_t Bno055Obj;

  struct bno055_accel_t Accel;
  struct bno055_mag_t Mag;
  struct bno055_gyro_t Gyro;
  struct bno055_euler_t Euler;
  struct bno055_quaternion_t Quaternion;
  struct bno055_linear_accel_t LinearAccel;
  struct bno055_gravity_t Gravity;
  struct bno055_accel_double_t AccelDouble;
  struct bno055_mag_double_t MagDouble;
  struct bno055_gyro_double_t GyroDouble;
  struct bno055_euler_double_t EulerDouble;
  struct bno055_linear_accel_double_t LinearAccelDouble;
  struct bno055_gravity_double_t GravityDouble;
  struct bno055_accel_float_t AccelFloat;
  struct bno055_mag_float_t MagFloat;
  struct bno055_gyro_float_t GyroFloat;
  struct bno055_euler_float_t EulerFloat;
  struct bno055_linear_accel_float_t LinearAccelFloat;
  struct bno055_gravity_float_t GravityFloat;
  float TemperatureFloat;
  struct bno055_accel_offset_t AccelOffset;
  struct bno055_gyro_offset_t GyroOffset;
  struct bno055_mag_offset_t MagOffset;
  struct bno055_sic_matrix_t SicMatrix;

}sCdrvBno055Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvBno055_Init(sCdrvBno055Obj * const me, uint8_t addrPinStat);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_BNO055_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

/**
******************************************************************************
* @file           : cdrv_gpio_ipwm.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_gpio_ipwm_H
#define __cdrv_gpio_ipwm_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\chrono\me_chrono.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
	bool _init;
  TysChrono_Obj _chronoDuty;
  TysChrono_Obj _chronoFrequency;
	uint8_t _risingCounter;
	uint8_t _fallingCounter;
	uint32_t Timeout_us;
  float32_t Duty_us;
  float32_t Interval_us;
  TysChrono_Obj ChronoTimeout;
	bool flag_first_time;
}sCdrvGpioIPwm_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvGpioIpwm_Init(sCdrvGpioIPwm_Obj * const me);
void fCdrvGpioIpwm_Run(sCdrvGpioIPwm_Obj * const me);
void fCdrvGpioIpwm_RisingEdgeCb(sCdrvGpioIPwm_Obj * const me);
void fCdrvGpioIpwm_FallingEdgeCb(sCdrvGpioIPwm_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_GPIO_IPWM_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

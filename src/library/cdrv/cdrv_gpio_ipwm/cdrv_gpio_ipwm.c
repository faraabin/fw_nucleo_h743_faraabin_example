/**
******************************************************************************
* @file           : cdrv_gpio_ipwm.c
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
#include "cdrv_gpio_ipwm.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_gpio_ipwm.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvGpioIpwm_Init(sCdrvGpioIPwm_Obj * const me) {
	
	me->_init = false;
  me->Duty_us = 0.0f;
	me->Interval_us = 0.0f;
	me->flag_first_time = true;
	me->_init = true;
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvGpioIpwm_Run(sCdrvGpioIPwm_Obj * const me) {
	
	if(!me->_init) {
		me->Duty_us = 0.0f;
		me->Interval_us = 0.0f;
		return;
	}
	
  if(meChrono_us_IsTimedOut(&me->ChronoTimeout)) {
    me->Duty_us = 0;
    me->Interval_us = 0;
  }
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvGpioIpwm_RisingEdgeCb(sCdrvGpioIPwm_Obj * const me) {
	
	meChrono_StartTimeout_(&me->ChronoTimeout, me->Timeout_us);
	
	if(me->flag_first_time == true) {
		me->flag_first_time = false;
	} else {
		me->Interval_us = meChrono_us_fElapsedInterval(&me->_chronoFrequency);
	}
	
	meChrono_Start(&me->_chronoFrequency);
	meChrono_Start(&me->_chronoDuty);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvGpioIpwm_FallingEdgeCb(sCdrvGpioIPwm_Obj * const me) {
	me->Duty_us = meChrono_us_fElapsedInterval(&me->_chronoDuty);
}

/*
===============================================================================
                    ##### cdrv_gpio_ipwm.c Private Functions #####
===============================================================================*/

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/


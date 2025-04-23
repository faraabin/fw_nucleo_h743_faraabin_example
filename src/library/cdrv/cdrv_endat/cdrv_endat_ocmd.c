/**
******************************************************************************
* @file           : cdrv_endat_ocmd.c
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
#include "cdrv_endat_ocmd.h"
#include "cdrv_endat.h"

#include "library\utility\chrono\me_chrono.h"

/* Private typedef -----------------------------------------------------------*/
FARAABIN_FUNCTION_GROUP_TYPE_DEF_(TysCdrvEnDat_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Functions Declaration #####                       ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
* @brief 
* 
*/
FARAABIN_FUNCTION_(cdrvEndat, READ, "help") {

  TysChrono_Obj chrono;

  FARAABIN_Function_LoopStartMs_(1000) {
    
    meChrono_Start(&chrono);
    uint8_t res = fCdrvEnDat_Update(me);
    float elapsed = meChrono_us_fElapsed(&chrono);
    if(res != 0) {
      FARAABIN_Printf_("\r\n(%f us)ERROR", elapsed);
    } else {
      FARAABIN_Printf_("\r\n(%f us)Encoder Value : (%u)%u, %f", elapsed, me->u_alarm, me->u_value_raw, me->u_value_degree);
    }
    
    FARAABIN_Function_LoopEnd_();
  }
  
  FARAABIN_FUNCTION_END_();
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Group Declaration #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
* @brief 
* 
*/
FARAABIN_FUNCTION_GROUP_(cdrvEndat, "help") {
  FARAABIN_FUNCTION_GROUP_ADD_(cdrvEndat, READ);
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

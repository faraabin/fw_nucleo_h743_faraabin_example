/**
******************************************************************************
* @file           : cdrv_ads79xx_ocmd.c
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
#include "cdrv_ads79xx_ocmd.h"
#include "cdrv_ads79xx.h"

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvAds79xx_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_ads79xx_ocmd.c Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(ads79xx, UpdateAi,
"type cmd help here") {
	
  meCONSOLE_LOOP_PAR_() {
		
		CdrvAds79xx_Update(me);
		
    meCONSOLE_LOOP_PAR_END_;
  }

  meCONSOLE_END_;
}

/*
===============================================================================
                    ##### cdrv_ads79xx_ocmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(ads79xx,
"type cmd help here") {
  meCONSOLE_ADD_CMD_(ads79xx, UpdateAi, 0);

  meCONSOLE_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

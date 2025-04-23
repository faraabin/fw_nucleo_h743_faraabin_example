/**
******************************************************************************
* @file           : cdrv_mtix_cmd.c
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
#include "cdrv_mtix_cmd.h"
#include "cdrv_mtix.h"

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sMTix_Object);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_mtix_cmd.c Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(cdrv_mtix, IRCC_CMD,
"type cmd help here") {
	
	eMTixInRunCompassCalibration cmd;
	
	mePRINTF_("Enter cmd:");
	mePRINTF_("0: Start rep motion");
	mePRINTF_("1: Stop rep motion");
	mePRINTF_("2: Store IRCC parameters");
	mePRINTF_("3: Get rep motion status");
	
	meCONSOLE_GET_INPUT_(1, 10000, "%d", &cmd);
	
	fCdrvMtix_InRunCompassCalibration(me, cmd);

  meCONSOLE_END_;
}

/*
===============================================================================
                    ##### cdrv_mtix_cmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(cdrv_mtix,
"type cmd help here") {
  meCONSOLE_ADD_CMD_(cdrv_mtix, IRCC_CMD, 0);

  meCONSOLE_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

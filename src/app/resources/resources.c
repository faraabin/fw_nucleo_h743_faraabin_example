/**
******************************************************************************
* @file           : resources.c
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
#include "resources.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
sResources resources;

/*
===============================================================================
                  ##### resource.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fResource_Init(void) {

  resources.reserve.Name = "reserve";
  resources.reserve.Type = eAM_RESOURCE_TYPE_NON_SHARABLE;

	return 0;
}

/*
===============================================================================
                  ##### resource.c Private Functions #####
===============================================================================*/

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

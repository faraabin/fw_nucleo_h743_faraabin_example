/**
******************************************************************************
* @file           : cdrv_bno055.c
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
#include "cdrv_bno055.h"
#include "library\core\me_type_tool.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_bno055.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @param ad0State 
 * @return uint8_t 
 */
uint8_t fCdrvBno055_Init(sCdrvBno055Obj * const me, uint8_t addrPinStat) {

  me->_init = false;
	
	if(me->Address != NULL) {
		if(addrPinStat == 0) {
			meGpio_Reset_(me->Address);
		} else {
			meGpio_Set_(me->Address);
		}
	}
	
  if(me->Bno055Obj.bus_read == NULL) {
    return 1;
  }
  if(me->Bno055Obj.bus_write == NULL) {
    return 1;
  }
  if(me->Bno055Obj.delay_msec == NULL) {
    return 1;
  }

	me->Bno055Obj.dev_addr = 0x50 + addrPinStat;
  if(bno055_init(&me->Bno055Obj) != 0) {
		return 1;
	}
	uint8_t chipId = 0;
	bno055_read_chip_id(&chipId);
	if(chipId != 0xA0) {
		return 1;
	}

  me->_init = true;
  return 0;
}

/*
===============================================================================
                ##### cdrv_bno055.c Private Functions #####
===============================================================================*/


/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

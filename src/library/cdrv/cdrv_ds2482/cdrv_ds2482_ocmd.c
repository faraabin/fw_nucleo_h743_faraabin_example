/**
******************************************************************************
* @file           : cdrv_ds2482_ocmd.c
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
#include "cdrv_ds2482_ocmd.h"
#include "cdrv_ds2482.h"

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sCdrvDs2482Obj);

/* Private define ------------------------------------------------------------*/
#define MUXIMUM_EXPECTED_DEVICE 20

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_ds2482_ocmd.c Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(cdrv_ds2482, SEARCH,
"type cmd help here") {

  TysChrono_Obj timer;
  uint64_t device_rom[MUXIMUM_EXPECTED_DEVICE];

  meChrono_Start(&timer);
  uint8_t count = fCdrvDs2482_OneWireScan(me, MUXIMUM_EXPECTED_DEVICE, device_rom);
  uint32_t elapsed = meChrono_us_Elapsed(&timer);

  mePRINTF_("\n(%luus)%u Device Found.", elapsed, count);
  for(uint16_t i = 0; i<count; i++) {
    mePRINTF_("\n%u- 0x%llx", i, device_rom[i]);
  }

  meCONSOLE_END_;
}

/*
===============================================================================
                    ##### cdrv_ds2482_ocmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(cdrv_ds2482,
"type cmd help here") {
  meCONSOLE_ADD_CMD_(cdrv_ds2482, SEARCH, 0);

  meCONSOLE_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

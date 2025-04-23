/**
******************************************************************************
* @file           : cdrv_nokia5110_cmd.c
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
#include "cdrv_nokia5110_cmd.h"
#include "cdrv_nokia5110.h"

#include <string.h>
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sCdrvNokia5110_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                        ##### cdrv_nokia5110_cmd.c Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(nokia5110, LCD_CLEAR,
"type cmd help here") {
  
  fCdrvNokia5110_LcdClear(me);

  meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(nokia5110, LCD_PRINT,
"type cmd help here") {
  
  char str[50] = {0x00};
  uint8_t row = 0;
  uint8_t col = 0;
  
  meCONSOLE_GET_INPUT_(3, 10000, "%d %d %s", &row, &col, &str);
  
  fCdrvNokia5110_Puts(str);
  
  fCdrvNokia5110_PCD8544_Refresh(me);

  meCONSOLE_END_;
}

/*
===============================================================================
                    ##### cdrv_nokia5110_cmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(nokia5110,
"type cmd help here") {
  meCONSOLE_ADD_CMD_(nokia5110, LCD_CLEAR, 0);
  meCONSOLE_ADD_CMD_(nokia5110, LCD_PRINT, 0);

  meCONSOLE_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

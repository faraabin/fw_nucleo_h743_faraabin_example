/**
 ******************************************************************************
 * @file           : mapp_function.c
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 FaraabinCo.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component
 * 
 * https://faraabinco.ir/
 * https://github.com/FaraabinCo
 *
 ******************************************************************************
 * @verbatim
 * @endverbatim
 */

/* Includes ------------------------------------------------------------------*/
#include "mapp_function.h"

#include "resources\resources.h"

#include "bsp.h"

#include "mapp_function_fn.h"
#include "library\utility\io\led_ofn.h"
#include "library\utility\io\led.h"

#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FARAABIN_CONTAINER_DEF_STATIC_(FunctionContainer);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappFunction = {
  .Name = "MappFunction",
  .Init = AppInit,
  .Start = AppStart,
  .Run = AppRun,
  .Terminate = AppTerminate
};

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/


/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
* @brief 
* 
* @return uint8_t 
*/
uint8_t AppInit(void) {

  return 0;
}

/**
 * @brief 
 * 
 * @param param 
 * @return uint8_t 
 */
uint8_t AppStart(void* param) {
  
  FARAABIN_Container_Init_(&FunctionContainer);
  FARAABIN_FunctionGroupType_Init_(&MappFunctionFn);
  FARAABIN_FunctionGroupType_Init_(&Led);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppTerminate(void) {

  return 0;
}

/**
 * @brief 
 * 
 */
FARAABIN_CONTAINER_FUNC_(FunctionContainer) {
  
  FARAABIN_SET_PATH_("TEST\\FUNCTION");
	
	FARAABIN_FUNCTION_GROUP_DICT_(MappFunctionFn);
  
  FARAABIN_FUNCTION_GROUP_OBJECT_DICT_(Led, Bsp.Dio.LedRed);
  FARAABIN_FUNCTION_GROUP_OBJECT_DICT_(Led, Bsp.Dio.LedGreen);
  FARAABIN_FUNCTION_GROUP_OBJECT_DICT_(Led, Bsp.Dio.LedBlue);
  
  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

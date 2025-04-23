/**
 ******************************************************************************
 * @file           : mapp_unity_fn.c
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
#include "mapp_unity_fn.h"
#include "mapp_unity_tests.h"

#if defined(FB_FEATURE_FLAG_MCU_CLI) && defined(FARAABIN_ENABLE)

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FARAABIN_FUNCTION_GROUP_TYPE_DEF_(void*);
static const char* argv[] = {"mapp_unity_fn.c", "-v"};

/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
FARAABIN_FUNCTION_(MappUnityFn, RUN_TESTS, "help") {

  fMappUnity_Tests_Run(2, argv);

  FARAABIN_FUNCTION_END_();
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
 * @brief 
 * 
 */
FARAABIN_FUNCTION_GROUP_(MappUnityFn, "help") {
  
  FARAABIN_FUNCTION_GROUP_ADD_(MappUnityFn, RUN_TESTS);

}

#endif

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

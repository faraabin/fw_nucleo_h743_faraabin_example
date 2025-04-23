/**
******************************************************************************
* @file           : mapp_variable_user_defined_cg.c
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
#include "mapp_variable_user_defined_cg.h"

#include "faraabin.h"

#include "mapp_variable_user_defined_cg_type.h"
#define TYPE_DICT
#include "mapp_variable_user_defined_cg_type.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static sCgTestStruct TestStructCg;
static eCgTestEnum TestEnumCg;

FARAABIN_CONTAINER_DEF_STATIC_(MappVariableUserDefinedCgContainer);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappVariableUserDefinedCg = {
  .Name = "MappVariableUserDefinedCg",
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

  FARAABIN_Container_Init_(&MappVariableUserDefinedCgContainer);
  FARAABIN_VAR_TYPE_STRUCT_INIT_(sCgTestStruct);
  FARAABIN_VAR_TYPE_ENUM_INIT_(eCgTestEnum);

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

FARAABIN_CONTAINER_FUNC_(MappVariableUserDefinedCgContainer) {
  
  FARAABIN_SET_PATH_("TEST_STRUCT_CG");
  
  FARAABIN_VAR_STRUCT_(TestStructCg, sCgTestStruct);

  FARAABIN_SET_PATH_("TEST_ENUM_CG");

  FARAABIN_VAR_ENUM_(TestEnumCg, eCgTestEnum);
  
  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

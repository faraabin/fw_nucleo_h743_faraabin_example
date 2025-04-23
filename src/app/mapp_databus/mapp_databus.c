/**
 ******************************************************************************
 * @file           : mapp_databus.c
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
#include "mapp_databus.h"

#include "resources\resources.h"

#include "faraabin.h"
#include "runtime_scaler.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FARAABIN_DATABUS_DEF_STATIC_(TestDatabus);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappDatabus = {
  .Name = "MappDatabus",
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

  FARAABIN_DATABUS_SET_VALUE_(TestDatabus.ChannelQty, 100);
  FARAABIN_DATABUS_SET_VALUE_(TestDatabus.BufferCaptureSize, 10);
  FARAABIN_DATABUS_SET_VALUE_(TestDatabus.StreamDivideBy, 10);
  FARAABIN_DataBus_Init_WithPath_(&TestDatabus, "path");
  FARAABIN_DataBus_StartStreamMode_(&TestDatabus);
  FARAABIN_DataBus_Enable_(&TestDatabus);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  RUN_EVERY_US_(DatabusTestRt, 1000) {
    
    FARAABIN_DataBus_Run_(&TestDatabus);
    
    RUN_END_;
  }

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

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

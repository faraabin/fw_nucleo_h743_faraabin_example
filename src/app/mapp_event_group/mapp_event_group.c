/**
 ******************************************************************************
 * @file           : mapp_event_group.c
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
#include "mapp_event_group.h"

#include "resources\resources.h"

#include "faraabin.h"
#include "runtime_scaler.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FARAABIN_EVENT_GROUP_DEF_STATIC_(TestEventGroup);
FARAABIN_EVENT_GROUP_DEF_STATIC_(TestHighSpeedEventGroup);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);
static void TestEventGroupUserTerminalCallback(uint8_t *data, uint16_t size);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappEventGroup = {
  .Name = "MappEventGroup",
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

  FARAABIN_EventGroup_Init_WithPath_(&TestEventGroup, "TEST");
  FARAABIN_EVENT_GROUP_SET_VALUE_(TestEventGroup.fpUserTerminalCallback, TestEventGroupUserTerminalCallback);
  FARAABIN_EventGroup_Enable_(&TestEventGroup);

  FARAABIN_EventGroup_Init_WithPath_(&TestHighSpeedEventGroup, "TEST_HIGH_SPEED");
  FARAABIN_EventGroup_Enable_(&TestHighSpeedEventGroup);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  RUN_EVERY_US_(HighSpeed, 1000) {

    static uint32_t cnt = 0;

    FARAABIN_PrintfTo_(&TestHighSpeedEventGroup, "Counter: %d", cnt);

    RUN_END_;
  }

  RUN_EVERY_MS_(EventGroupRt, 1000) {

    static uint8_t cnt = 0;
    
    FARAABIN_PrintfTo_(&TestEventGroup, "Testing...:%u", cnt);
    FARAABIN_PutsTo_(&TestEventGroup, "Sending info to Faraabin");
    FARAABIN_PutsWarningTo_(&TestEventGroup, "Sending warning to Faraabin");
    FARAABIN_PutsErrorTo_(&TestEventGroup, "Sending error to Faraabin");
    
    FARAABIN_PrintfToTerminal_(&TestEventGroup, "\r\nTerminal:%s", "hello");

    cnt++;

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

/**
 * @brief 
 * 
 * @param data 
 * @param size 
 */
static void TestEventGroupUserTerminalCallback(uint8_t *data, uint16_t size) {
  
  FARAABIN_PrintfToTerminal_(&TestEventGroup, "\r\nLoop Terminal:%s", data);
  
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

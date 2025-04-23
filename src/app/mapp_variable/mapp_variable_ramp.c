/**
******************************************************************************
* @file           : mapp_variable_ramp.c
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
#include "mapp_variable_ramp.h"

#include "runtime_scaler.h"
#include "library\utility\dsp\ramp.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FARAABIN_CONTAINER_DEF_(MappVariableRampContainer);
FARAABIN_EVENT_GROUP_DEF_STATIC_(MappVariableRampReportEventGroup);
FARAABIN_EVENT_GROUP_DEF_STATIC_(MappVariableRampProgressEventGroup);

static sRamp Ramp;
static bool ResetRamp;
static float InitVal;
static float FinalVal;
static uint32_t DurationMs;
static float RampValue;

static bool ReportOnce[4];

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappVariableRamp = {
  .Name = "MappVariableRamp",
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

  FARAABIN_Container_Init_(&MappVariableRampContainer);
  
  FARAABIN_EventGroup_Init_(&MappVariableRampReportEventGroup);
  FARAABIN_EventGroup_Enable_(&MappVariableRampReportEventGroup);
  
  FARAABIN_EventGroup_Init_(&MappVariableRampProgressEventGroup);
  FARAABIN_EventGroup_Enable_(&MappVariableRampProgressEventGroup);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {
  
  if(ResetRamp) {
    
    ResetRamp = false;
    
    Ramp.InitValue = InitVal;
    Ramp.FinalValue = FinalVal;
    Ramp.DurationMs = DurationMs;
    fRamp_Init(&Ramp);
    
    ReportOnce[0] = false;
    ReportOnce[1] = false;
    ReportOnce[2] = false;
    ReportOnce[3] = false;
    
    FARAABIN_PrintfTo_(&MappVariableRampProgressEventGroup, "Progress: %d Percent", 0);
    
  }
  
  RampValue = fRamp_Step(&Ramp);
  
  if(RampValue >= (0.25f * FinalVal)) {
    
    if(ReportOnce[0] == false) {
      
      ReportOnce[0] = true;
      FARAABIN_PrintfTo_(&MappVariableRampProgressEventGroup, "Progress: %d Percent", 25);
      
    }
  }
  
  if(RampValue >= (0.50f * FinalVal)) {
    
    if(ReportOnce[1] == false) {
      
      ReportOnce[1] = true;
      FARAABIN_PrintfTo_(&MappVariableRampProgressEventGroup, "Progress: %d Percent", 50);
      
    }
  }
  
  if(RampValue >= (0.75f * FinalVal)) {
    
    if(ReportOnce[2] == false) {
      
      ReportOnce[2] = true;
      FARAABIN_PrintfTo_(&MappVariableRampProgressEventGroup, "Progress: %d Percent", 75);
      
    }
  }
  
  if(RampValue >= FinalVal) {
    
    if(ReportOnce[3] == false) {
      
      ReportOnce[3] = true;
      FARAABIN_PrintfTo_(&MappVariableRampProgressEventGroup, "Progress: %d Percent", 100);
      
    }
  }
  
  RUN_EVERY_S_(Report, 1) {
    
    FARAABIN_PrintfTo_(&MappVariableRampReportEventGroup, "Current ramp value: %f", RampValue);
    
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
 */
FARAABIN_CONTAINER_FUNC_(MappVariableRampContainer) {
  
  FARAABIN_VAR_BOOL_(ResetRamp);
  FARAABIN_VAR_F32_(InitVal);
  FARAABIN_VAR_F32_(FinalVal);
  FARAABIN_VAR_F32_(RampValue);
  FARAABIN_VAR_U32_(DurationMs);
  
  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

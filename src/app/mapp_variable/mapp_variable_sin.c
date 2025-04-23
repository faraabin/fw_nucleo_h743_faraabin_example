/**
******************************************************************************
* @file           : mapp_variable_sin.c
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
#include "mapp_variable_sin.h"

#include "runtime_scaler.h"
#include "cpu_profiler_wrapper.h"

#include "stm32h7xx_hal.h"
#include <arm_math.h>

/* Private define ------------------------------------------------------------*/
#define SIN_PERIOD_US (1000)

#ifdef PI
#undef PI
#endif
#define PI            (3.1415926535897932384626433832795)

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static double Frequency;
static double FrequencyOld;
static double Amplitude;
static double AmplitudeOld;
static double OutU;
static double OutV;
static double OutW;
static bool IsActive;
static double t;

static sChrono ChronoTiming;

FARAABIN_CONTAINER_DEF_(MappVariableSinContainer);
FARAABIN_EVENT_GROUP_DEF_STATIC_(AmplitudeEventGroup);
FARAABIN_EVENT_GROUP_DEF_STATIC_(FrequencyEventGroup);
CPU_PROFILER_CODEBLOCK_DEF_(SinCodeblock);
CPU_PROFILER_SECTION_DEF_(Arrange);
CPU_PROFILER_SECTION_DEF_(Calculation);
CPU_PROFILER_SECTION_DEF_(Debug);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappVariableSin = {
  .Name = "MappVariableSin",
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
  
  Frequency = 0.0;
  FrequencyOld = 0.0;
  Amplitude = 0.0;
  AmplitudeOld = 0.0;

  OutU = 0.0;
  OutV = 0.0;
  OutW = 0.0;

  IsActive = false;

  fChrono_StartTimeoutUs(&ChronoTiming, SIN_PERIOD_US);

  return 0;
}

/**
 * @brief 
 * 
 * @param param 
 * @return uint8_t 
 */
uint8_t AppStart(void* param) {

  FARAABIN_Container_Init_(&MappVariableSinContainer);
  
  FARAABIN_EventGroup_Init_(&AmplitudeEventGroup);
  FARAABIN_EventGroup_Enable_(&AmplitudeEventGroup);
  FARAABIN_EventGroup_Init_(&FrequencyEventGroup);
  FARAABIN_EventGroup_Enable_(&FrequencyEventGroup);
  fCpuProfiler_CodeBlockInit_(&SinCodeblock, 3);
  fCpuProfiler_CodeBlockAddSection_(&SinCodeblock, &Arrange);
  fCpuProfiler_CodeBlockAddSection_(&SinCodeblock, &Calculation);
  fCpuProfiler_CodeBlockAddSection_(&SinCodeblock, &Debug);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  if(!IsActive) {
    
    OutU = 0.0;
    OutV = 0.0;
    OutW = 0.0;

    return 0;
  }

  if(fChrono_IsTimeout(&ChronoTiming)) {

    fCpuProfiler_CodeBlockBegin_(&SinCodeblock);

    fCpuProfiler_SectionBegin_(&Arrange);
    
    fChrono_StartTimeoutUs(&ChronoTiming, SIN_PERIOD_US);

    t = t + ((SIN_PERIOD_US) / 1000000.0);

    double w = 2.0 * PI * Frequency * t;
    if(w > 2.0 * PI) {
      w = w - (2.0 * PI);
    }

    fCpuProfiler_SectionEnd_(&Arrange);

    fCpuProfiler_SectionBegin_(&Calculation);

    OutU = Amplitude * arm_sin_f32(w);
    OutV = Amplitude * arm_sin_f32(w + (2.0 * PI / 3.0));
    OutW = Amplitude * arm_sin_f32(w - (2.0 * PI / 3.0));

    fCpuProfiler_SectionEnd_(&Calculation);

    fCpuProfiler_SectionBegin_(&Debug);

    if(AmplitudeOld != Amplitude) {

      AmplitudeOld = Amplitude;

      FARAABIN_PrintfWarningTo_(&AmplitudeEventGroup, "Amplitude has been changed!");
    }

    if(FrequencyOld != Frequency) {

      FrequencyOld = Frequency;

      FARAABIN_PrintfWarningTo_(&FrequencyEventGroup, "Frequency has been changed!");
    }

    fCpuProfiler_SectionBegin_(&Debug);

    fCpuProfiler_CodeBlockEnd_(&SinCodeblock);

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
FARAABIN_CONTAINER_FUNC_(MappVariableSinContainer) {
  
  FARAABIN_VAR_BOOL_(IsActive);
  FARAABIN_VAR_F64_(OutU);
  FARAABIN_VAR_F64_(OutV);
  FARAABIN_VAR_F64_(OutW);
  FARAABIN_VAR_F64_(Frequency);
  FARAABIN_VAR_F64_(Amplitude);

  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

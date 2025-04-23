/**
 ******************************************************************************
 * @file           : mapp_exp_board.c
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 FaraabinCo.
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
#include "mapp_exp_board.h"
#include "resources\resources.h"

#include "mapp_exp_board_fn.h"

#include "faraabin.h"

#include <math.h>
#include "arm_math.h"

/* Private define ------------------------------------------------------------*/
#define RUNTIME_PERIOD_US (1000)
#define OMEGA             (2.0 * (double)PI * Frequency)

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/**
 * @brief enum for defining generated wave type.
 * 
 */
typedef enum {

  eWAVE_TYPE_NONE = 0,
  eWAVE_TYPE_PULSE_TRAIN,
  eWAVE_TYPE_SAW_TOOTH,
  eWAVE_TYPE_SIN,

}eWaveType;

/* Private variables ---------------------------------------------------------*/
static eWaveType WaveType;
static float64_t Frequency;
static float64_t Amplitude;
static float64_t Output;
static uint32_t Execution;
static uint32_t Interval;

static double t;
static double OmegaT;
static sChrono RuntimeChrono;
static sChrono FreqChrono;
static uint32_t TickBegin;
static uint32_t TickEnd;

FARAABIN_CONTAINER_DEF_STATIC_(ExpBoardContainer);
FARAABIN_DATABUS_DEF_STATIC_(ExpBoardDatabus);
FARAABIN_EVENT_GROUP_DEF_STATIC_(ExpBoardEvType);
FARAABIN_EVENT_GROUP_DEF_STATIC_(ExpBoardEvFreq);
FARAABIN_EVENT_GROUP_DEF_STATIC_(ExpBoardEvAmp);
FARAABIN_EVENT_GROUP_DEF_STATIC_(ExpBoardEvDuty);
FARAABIN_VAR_TYPE_DEF_STATIC_(eWaveType);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappExpBoard = {
  .Name = "MappExpBoard",
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

  FARAABIN_Container_Init_(&ExpBoardContainer);

  FARAABIN_VAR_TYPE_ENUM_INIT_(eWaveType);
  
  FARAABIN_DATABUS_SET_VALUE_(ExpBoardDatabus.ChannelQty, 5);
  FARAABIN_DATABUS_SET_VALUE_(ExpBoardDatabus.BufferCaptureSize, 100);
  FARAABIN_DATABUS_SET_VALUE_(ExpBoardDatabus.StreamDivideBy, 10);
  FARAABIN_DataBus_Init_(&ExpBoardDatabus);
  FARAABIN_DataBus_StartStreamMode_(&ExpBoardDatabus);
  FARAABIN_DataBus_AttachVariable_F64_(&ExpBoardDatabus, &Output);
  FARAABIN_DataBus_Enable_(&ExpBoardDatabus);

  FARAABIN_EventGroup_Init_(&ExpBoardEvType);
  FARAABIN_EventGroup_Init_(&ExpBoardEvAmp);
  FARAABIN_EventGroup_Init_(&ExpBoardEvFreq);
  FARAABIN_EventGroup_Init_(&ExpBoardEvDuty);

  FARAABIN_FunctionGroupType_Init_(&MappExpBoardFn);

  WaveType = eWAVE_TYPE_NONE;
  Frequency = 0.0;
  Amplitude = 0.0;
  t = 0.0;

  return 0;
}

/**
 * @brief 
 * 
 * @param param 
 * @return uint8_t 
 */
uint8_t AppStart(void* param) {

  fChrono_StartTimeoutUs(&RuntimeChrono, RUNTIME_PERIOD_US);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  if(fChrono_IsTimeout(&RuntimeChrono)) {

    static uint32_t lastTickBegin = 0;
    
    TickBegin = fChrono_GetTick();

    fChrono_StartTimeoutUs(&RuntimeChrono, RUNTIME_PERIOD_US);
    t = t + ((double)RUNTIME_PERIOD_US / 1000000.0);

    switch (WaveType) {
    case eWAVE_TYPE_NONE: {
      
      Output = 0;
      break;
    }
    case eWAVE_TYPE_PULSE_TRAIN: {
      
      if(fChrono_IsTimeout(&FreqChrono)) {
        
        timeUs_t interval = (timeUs_t)((1.0 / Frequency) * 1000000) / 2;
        if(Frequency == 0.0) {
          interval = 0;
        }
        fChrono_StartTimeoutUs(&FreqChrono, interval);

        static bool pulseState = false;
        pulseState = !pulseState;
        
        Output = Amplitude * (double)pulseState;
        
      }
      
      break;
    }
    case eWAVE_TYPE_SAW_TOOTH: {

      Output = Amplitude * fmod(t, (1.0 / Frequency));
      
      break;
    }
    case eWAVE_TYPE_SIN: {

      OmegaT = OMEGA * t;
      if(OmegaT > (2.0 * (double)PI)) {
        OmegaT = OmegaT - (2.0 * (double)PI);
      }

      Output = Amplitude * arm_sin_f32(OmegaT);

      break;
    }
    default: {
      Output = 0.0;
      break;
    }
    }

    static eWaveType OldType = eWAVE_TYPE_NONE;
    if(OldType != WaveType) {
      
      FARAABIN_SendEventTo_(&ExpBoardEvType, eWaveType, WaveType);
      OldType = WaveType;

    }

    static double OldAmp = 0.0;
    if(OldAmp != Amplitude) {
      
      FARAABIN_PrintfWarningTo_(&ExpBoardEvAmp, "Amplitude changed from %lf to %lf", OldAmp, Amplitude);
      OldAmp = Amplitude;

    }

    static double OldFreq = 0.0;
    if(OldFreq != Frequency) {
      
      FARAABIN_PrintfWarningTo_(&ExpBoardEvFreq, "Frequency changed from %lf to %lf", OldFreq, Frequency);
      OldFreq = Frequency;
      timeUs_t interval = (timeUs_t)((1.0 / Frequency) * 1000000) / 2;
      if(Frequency == 0.0) {
        interval = 0;
      }
      fChrono_StartTimeoutUs(&FreqChrono, interval);

    }
    
    FARAABIN_DataBus_Run_(&ExpBoardDatabus);
    
    TickEnd = fChrono_GetTick();

    Interval = fChrono_TimeSpanUs(lastTickBegin, TickBegin);
    Execution = fChrono_TimeSpanUs(TickBegin, TickEnd);
    
    lastTickBegin= TickBegin;

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
 * @brief This function is used to define eWaveType fields to faraabin.
 * 
 */
static FARAABIN_VAR_TYPE_ENUM_FUNC_(eWaveType) {

  FARAABIN_VAR_TYPE_ENUM_FUNC_START_(eWaveType);

  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eWAVE_TYPE_NONE);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eWAVE_TYPE_PULSE_TRAIN);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eWAVE_TYPE_SAW_TOOTH);
  FARAABIN_VAR_TYPE_ENUM_MEMBER_(eWAVE_TYPE_SIN);

  FARAABIN_VAR_TYPE_ENUM_FUNC_END_(eWaveType);
}

/**
 * @brief This function is used to define all variables in the container to faraabin.
 * 
 */
FARAABIN_CONTAINER_FUNC_(ExpBoardContainer) {

  FARAABIN_VAR_ENUM_(WaveType, eWaveType);

  FARAABIN_VAR_F64_(Frequency);
  FARAABIN_VAR_F64_(Amplitude);
  FARAABIN_VAR_F64_(Output);

  FARAABIN_VAR_U32_(Execution);
  FARAABIN_VAR_U32_(Interval);

  FARAABIN_FUNCTION_GROUP_DICT_(MappExpBoardFn);

  FARAABIN_CONTAINER_FUNC_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

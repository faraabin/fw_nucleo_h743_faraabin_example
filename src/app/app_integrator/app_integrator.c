/**
******************************************************************************
* @file           : app_integrator.c
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
#include "app_integrator.h"
#include "app_manager\app_manager_fn.h"

#include "app\resources\resources.h"

#include "app\mapp_databus\mapp_databus.h"
#include "app\mapp_event_group\mapp_event_group.h"
#include "app\mapp_code_block\mapp_code_block.h"
#include "app\mapp_cpu_profiler\mapp_cpu_profiler.h"
#include "app\mapp_state_machine\mapp_state_machine.h"
#include "app\mapp_fsm\mapp_fsm.h"
#include "app\mapp_function\mapp_function.h"
#include "app\mapp_variable\mapp_variable_primitive.h"
#include "app\mapp_variable\mapp_variable_sin.h"
#include "app\mapp_variable\mapp_variable_ramp.h"
#include "app\mapp_variable\mapp_variable_user_defined.h"
#include "app\mapp_variable\mapp_variable_user_defined_cg.h"
#include "app\mapp_exp_board\mapp_exp_board.h"
#include "app\mapp_unity\mapp_unity.h"
#include "app\mapp_comm_mbs\mapp_comm_mbs.h"

#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
FARAABIN_EVENT_GROUP_DEF_(appManagerEventGroup);
FARAABIN_CONTAINER_DEF_(appManagerContainer);

/* Private function prototypes -----------------------------------------------*/
static void ErrorEvent(sAppManagerErrorOccuredEventArgs *ev);
static void ResourceConflictEvent(sAppManagerResourceConflictDetectedEventArgs *ev);
static void AppInitEvent(sAppInitializedEventArgs *ev);
static void AppStartEvent(sAppStartedEventArgs *ev);
static void AppTerminateEvent(sAppTerminatedEventArgs *ev);
static void AppEmgcFaultEvent(sAppEmergencyFaultOccuredEventArgs *ev);

/**
 * @brief 
 * 
 */
FARAABIN_CONTAINER_FUNC_(appManagerContainer) {
  
  FARAABIN_FUNCTION_GROUP_DICT_WP_(appManagerFn, "APP\\FUNC");
  
  FARAABIN_CONTAINER_FUNC_END_;
  
}

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### app_integrator.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t fAppIntegrator_Init(void) {
  
  FARAABIN_EventGroup_Init_WithPath_(&appManagerEventGroup, "APP\\APP_INTEGRATOR");
  
  AppManager.fpErrorOccuredEvent = ErrorEvent;
  AppManager.fpResourceConflictDetectedEvent = ResourceConflictEvent;
  AppManager.fpAppInitializedEvent = AppInitEvent;
  AppManager.fpAppStartedEvent = AppStartEvent;
  AppManager.fpAppTerminatedEvent = AppTerminateEvent;
  AppManager.fpAppEmergencyFaultOccuredEvent = AppEmgcFaultEvent;
  fAppManager_Init();
  
  fAppManager_AddApp(&MappCodeBlock);
  fAppManager_AddApp(&MappCpuProfiler);
  fAppManager_AddApp(&MappDatabus);
  fAppManager_AddApp(&MappEventGroup);
  fAppManager_AddApp(&MappFunction);
  fAppManager_AddApp(&MappStateMachine);
  fAppManager_AddApp(&MappFsm);
  fAppManager_AddApp(&MappVariablePrimitive);
  fAppManager_AddApp(&MappVariableSin);
  fAppManager_AddApp(&MappVariableRamp);
  fAppManager_AddApp(&MappVariableUserDefined);
  fAppManager_AddApp(&MappVariableUserDefinedCg);
  fAppManager_AddApp(&MappUnity);
//	fAppManager_AddApp(&MappCommMbs);
//  fAppManager_AddApp(&MappExpBoard);
	
//	fAppManager_StartApp(&MappCodeBlock, NULL);
//	fAppManager_StartApp(&MappCpuProfiler, NULL);
//  fAppManager_StartApp(&MappDatabus, NULL);
//  fAppManager_StartApp(&MappEventGroup, NULL);
  fAppManager_StartApp(&MappFunction, NULL);
  fAppManager_StartApp(&MappStateMachine, NULL);
//  fAppManager_StartApp(&MappFsm, NULL);
  fAppManager_StartApp(&MappVariablePrimitive, NULL);
//  fAppManager_StartApp(&MappVariableSin, NULL);
//  fAppManager_StartApp(&MappVariableRamp, NULL);
//  fAppManager_StartApp(&MappVariableUserDefined, NULL);
//  fAppManager_StartApp(&MappVariableUserDefinedCg, NULL);
//  fAppManager_StartApp(&MappUnity, NULL);
//  fAppManager_StartApp(&MappCommMbs, NULL);
//  fAppManager_StartApp(&MappExpBoard, NULL);
  
  FARAABIN_Container_Init_(&appManagerContainer);
  FARAABIN_FunctionGroupType_Init_(&appManagerFn);
  
  return 0;
}

/**
 * @brief 
 * 
 */
void fAppIntegrator_Run(void) {
  
  fAppManager_Run();
  fFaraabin_Run();
  
}

/*
===============================================================================
                ##### app_integrator.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param sender: Pointer to the sender of this event.
 * @param e: event arguments that have been sent.
 */
static void ErrorEvent(sAppManagerErrorOccuredEventArgs *ev) {
  
  switch(ev->ErrorCode) {
    case eAM_ERROR_NOT_ENOUGH_SPACE:
    {
      FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "AppManger ERROR [NOT ENOUGH SPACE]. APP: %s", ev->App->Name);
      break;
    }
    case eAM_ERROR_APP_NOT_FOUND:
    {
      FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "AppManger ERROR [APP NOT FOUND]. APP: %s", ev->App->Name);
      break;
    }
    case eAM_ERROR_APP_INIT_FAILED:
    {
      FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "AppManger ERROR [APP INIT FAILED]. APP: %s", ev->App->Name);
      break;
    }
    case eAM_ERROR_APP_START_FAILED:
    {
      FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "AppManger ERROR [APP START FAILED]. APP: %s", ev->App->Name);
      break;
    }
    case eAM_ERROR_APP_TERMINATE_FAILED:
    {
      FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "AppManger ERROR [APP TERMINATE FAILED]. APP: %s", ev->App->Name);
      break;
    }
    case eAM_ERROR_APP_EMERGENCY_FAULT:
    {
      FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "AppManger ERROR [APP EMERGENCY FAULT]. APP: %s", ev->App->Name);
      break;
    }
    case eAM_ERROR_NONE:
    default:
    {
      break;
    }
  }
  
}

/**
 * @brief 
 * 
 * @param sender: Pointer to the sender of this event.
 * @param e: event arguments that have been sent.
 */
static void ResourceConflictEvent(sAppManagerResourceConflictDetectedEventArgs *ev) {
  
  FARAABIN_PrintfWarningTo_(&appManagerEventGroup, "Resource %s is used by app %s and can't add it to app %s.", ev->ConflictingApp->Name, ev->Resource->Name, ev->App->Name);
  
}

/**
 * @brief 
 * 
 * @param sender: Pointer to the sender of this event.
 * @param e: event arguments that have been sent.
 */
static void AppInitEvent(sAppInitializedEventArgs *ev) {
  
  FARAABIN_PrintfTo_(&appManagerEventGroup, "App %s initialized successfully (%d us).", ev->App->Name, ev->ElapsedTimeUs);
  
}

/**
 * @brief 
 * 
 * @param sender: Pointer to the sender of this event.
 * @param e: event arguments that have been sent.
 */
static void AppStartEvent(sAppStartedEventArgs *ev) {
  
  FARAABIN_PrintfTo_(&appManagerEventGroup, "App %s started successfully (%d us).", ev->App->Name, ev->ElapsedTimeUs);
  
}

/**
 * @brief 
 * 
 * @param sender: Pointer to the sender of this event.
 * @param e: event arguments that have been sent.
 */
static void AppTerminateEvent(sAppTerminatedEventArgs *ev) {
  
  FARAABIN_PrintfTo_(&appManagerEventGroup, "App %s terminated successfully (%d us).", ev->App->Name, ev->ElapsedTimeUs);
  
}

/**
 * @brief 
 * 
 * @param sender: Pointer to the sender of this event.
 * @param e: event arguments that have been sent.
 */
static void AppEmgcFaultEvent(sAppEmergencyFaultOccuredEventArgs *ev) {
  
  FARAABIN_PrintfErrorTo_(&appManagerEventGroup, "App %s Emergency fault occured.", ev->App->Name);
  
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

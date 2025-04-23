/**
 ******************************************************************************
 * @file           : mapp_fsm.c
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
#include "mapp_fsm.h"
#include "resources\resources.h"

#include "state_machine\state_machine_wrapper.h"
#include "runtime_scaler.h"
#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
STATE_MACHINE_DEF_(FSM);

STATE_MACHINE_STATE_DEF_(s1);
STATE_MACHINE_STATE_DEF_(s2);
STATE_MACHINE_STATE_DEF_(s3);
STATE_MACHINE_STATE_DEF_(s4);
STATE_MACHINE_STATE_DEF_(s5);

STATE_MACHINE_TRANSITION_DEF_(t11);
STATE_MACHINE_TRANSITION_DEF_(t12);
STATE_MACHINE_TRANSITION_DEF_(t21);
STATE_MACHINE_TRANSITION_DEF_(t23);
STATE_MACHINE_TRANSITION_DEF_(t34);
STATE_MACHINE_TRANSITION_DEF_(t41);
STATE_MACHINE_TRANSITION_DEF_(t54);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappFsm = {
  .Name = "MappFsm",
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

  // Initializing state machine
  if(StateMachine_Init_(&FSM, 5, 7, &s1) != SM_OK) {
    return 1;
  }

  // Configuring states
  uint8_t stateCounter = 1;

  if(StateMachine_AddState_(&FSM, &s1, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&FSM, &s2, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&FSM, &s3, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&FSM, &s4, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&FSM, &s5, stateCounter++) != SM_OK) {
    return 1;
  }

  // Configuring transitions
  uint8_t transitionCounter = 1;

  if(StateMachine_AddTransition_(&FSM, &t11, transitionCounter++, &s1, &s1) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&FSM, &t12, transitionCounter++, &s1, &s2) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&FSM, &t21, transitionCounter++, &s2, &s1) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&FSM, &t23, transitionCounter++, &s2, &s3) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&FSM, &t34, transitionCounter++, &s3, &s4) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&FSM, &t41, transitionCounter++, &s4, &s1) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&FSM, &t54, transitionCounter++, &s5, &s4) != SM_OK) {
    return 1;
  }

  StateMachine_Start_(&FSM);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  RUN_EVERY_MS_(FsmRt, 100) {

    uint8_t smEvent = 0; // TODO: Events can be passed to state machine through this!
    
    fStateMachine_Step(&FSM, &smEvent);
    
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
 * @brief Action function of the initial transition in state machine.
 * 
 */
STATE_MACHINE_INITIAL_TRANSITION_ACTION_(FSM) {

}

/**
 * @brief Entry function of the s1.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s1, void *sender) {

}

/**
 * @brief Do function of the s1.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s1, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s1.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s1, void *sender) {

}

/**
 * @brief Entry function of the s2.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s2, void *sender) {

}

/**
 * @brief Do function of the s2.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s2, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s2.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s2, void *sender) {

}

/**
 * @brief Entry function of the s3.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s3, void *sender) {

}

/**
 * @brief Do function of the s3.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s3, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s3.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s3, void *sender) {

}

/**
 * @brief Entry function of the s4.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s4, void *sender) {

}

/**
 * @brief Do function of the s4.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s4, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s4.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s4, void *sender) {

}

/**
 * @brief Entry function of the s5.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s5, void *sender) {

}

/**
 * @brief Do function of the s5.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s5, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s5.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s5, void *sender) {

}

/**
 * @brief Event function of the transition t11.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t11, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t11.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t11, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t11.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t11, void *sender) {

}

/**
 * @brief Event function of the transition t12.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t12, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t12.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t12, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t12.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t12, void *sender) {

}

/**
 * @brief Event function of the transition t21.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t21, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t21.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t21, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t21.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t21, void *sender) {

}

/**
 * @brief Event function of the transition t23.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t23, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t23.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t23, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t23.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t23, void *sender) {

}


/**
 * @brief Event function of the transition t34.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t34, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t34.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t34, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t34.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t34, void *sender) {

}

/**
 * @brief Event function of the transition t41.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t41, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t41.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t41, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t41.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t41, void *sender) {

}

/**
 * @brief Event function of the transition t54.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t54, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t54.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t54, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t54.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t54, void *sender) {

}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

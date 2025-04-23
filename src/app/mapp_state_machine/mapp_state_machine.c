/**
******************************************************************************
* @file           : mapp_sm.c
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
#include "mapp_state_machine.h"

#include "resources\resources.h"

#include "state_machine\state_machine_wrapper.h"
#include "runtime_scaler.h"
#include "faraabin.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
STATE_MACHINE_DEF_(TestStateMachine);

STATE_MACHINE_COMPOSITE_STATE_DEF_(s1);
STATE_MACHINE_COMPOSITE_STATE_DEF_(s1a);
STATE_MACHINE_STATE_DEF_(s1aa);
STATE_MACHINE_STATE_DEF_(s1ab);
STATE_MACHINE_STATE_DEF_(s1b);
STATE_MACHINE_STATE_DEF_(s1c);
STATE_MACHINE_COMPOSITE_STATE_DEF_(s2);
STATE_MACHINE_STATE_DEF_(s2a);
STATE_MACHINE_COMPOSITE_STATE_DEF_(s2b);
STATE_MACHINE_STATE_DEF_(s2ba);
STATE_MACHINE_STATE_DEF_(s2bb);
STATE_MACHINE_COMPOSITE_STATE_DEF_(s3);
STATE_MACHINE_COMPOSITE_STATE_DEF_(s3a);
STATE_MACHINE_COMPOSITE_STATE_DEF_(s3aa);
STATE_MACHINE_STATE_DEF_(s3aaa);
STATE_MACHINE_STATE_DEF_(st);

STATE_MACHINE_TRANSITION_DEF_(t11);
STATE_MACHINE_TRANSITION_DEF_(t1b1a);
STATE_MACHINE_TRANSITION_DEF_(t1c1b);
STATE_MACHINE_TRANSITION_DEF_(t1a1aa);
STATE_MACHINE_TRANSITION_DEF_(t1a1c);
STATE_MACHINE_TRANSITION_DEF_(t1a1a);
STATE_MACHINE_TRANSITION_DEF_(t1ab1aa);
STATE_MACHINE_TRANSITION_DEF_(t1aa1ab);
STATE_MACHINE_TRANSITION_DEF_(t1ab1ab);
STATE_MACHINE_TRANSITION_DEF_(t1aa1);
STATE_MACHINE_TRANSITION_DEF_(t12);
STATE_MACHINE_TRANSITION_DEF_(t21);
STATE_MACHINE_TRANSITION_DEF_(t22);
STATE_MACHINE_TRANSITION_DEF_(t2t);
STATE_MACHINE_TRANSITION_DEF_(t23);
STATE_MACHINE_TRANSITION_DEF_(t32);
STATE_MACHINE_TRANSITION_DEF_(t2bb1aa);
STATE_MACHINE_TRANSITION_DEF_(t2bb2a);
STATE_MACHINE_TRANSITION_DEF_(t2a2ba);
STATE_MACHINE_TRANSITION_DEF_(t2ba2bb);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

static void TransitionOccuredEvent(void *sender, sTransitionEventArgs *e);
static void TransitionRejectedEvent(void *sender, sTransitionEventArgs *e);
static void TransitionActionExecutedEvent(void *sender, sTransitionEventArgs *e);
static void StateEnteredEvent(void *sender, sStateEventArgs *e);
static void StateDoneEvent(void *sender, sStateEventArgs *e);
static void StateExitedEvent(void *sender, sStateEventArgs *e);
static void TransitionEvtCheckingEvent(void *sender, sTransitionCheckingArgs *e);
static void TransitionGuardCheckingEvent(void *sender, sTransitionCheckingArgs *e);
static void ExecutionErrorOccuredEvent(void *sender, sExecutionErrorArgs *e);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappStateMachine = {
  .Name = "MappStateMachine",
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
  if(StateMachine_Init_(&TestStateMachine, 16, 20, &s1) != SM_OK) {
    return 1;
  }

  // Configuring states
  uint8_t stateCounter = 1;

  if(StateMachine_AddState_(&TestStateMachine, &s1, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s1a, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s1aa, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s1ab, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s1b, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s1c, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s2, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s2a, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s2b, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s2ba, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s2bb, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s3, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s3a, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s3aa, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &s3aaa, stateCounter++) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddState_(&TestStateMachine, &st, stateCounter++) != SM_OK) {
    return 1;
  }

  // Configuring parents
  if(fStateMachine_SetStateParent(&TestStateMachine, &s1a, &s1) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s1aa, &s1a) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s1ab, &s1a) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s1b, &s1) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s1c, &s1) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s2a, &s2) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s2b, &s2) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s2ba, &s2b) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s2bb, &s2b) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s3a, &s3) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s3aa, &s3a) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateParent(&TestStateMachine, &s3aaa, &s3aa) != SM_OK) {
    return 1;
  }

  // Configuring first child
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s1, &s1a) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s1a, &s1aa) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s2, &s2a) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s2b, &s2ba) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s3, &s3a) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s3a, &s3aa) != SM_OK) {
    return 1;
  }
  if(fStateMachine_SetStateFirstChild(&TestStateMachine, &s3aa, &s3aaa) != SM_OK) {
    return 1;
  }
  
  // Configuring transitions
  uint8_t transitionCounter = 1;

  if(StateMachine_AddTransition_(&TestStateMachine, &t11, transitionCounter++, &s1, &s1) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1b1a, transitionCounter++, &s1b, &s1a) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1c1b, transitionCounter++, &s1c, &s1b) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1a1aa, transitionCounter++, &s1a, &s1aa) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1a1c, transitionCounter++, &s1a, &s1c) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1a1a, transitionCounter++, &s1a, &s1a) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1ab1aa, transitionCounter++, &s1ab, &s1aa) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1aa1ab, transitionCounter++, &s1aa, &s1ab) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1ab1ab, transitionCounter++, &s1ab, &s1ab) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t1aa1, transitionCounter++, &s1aa, &s1) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t12, transitionCounter++, &s1, &s2) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t21, transitionCounter++, &s2, &s1) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t22, transitionCounter++, &s2, &s2) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t2t, transitionCounter++, &s2, &st) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t23, transitionCounter++, &s2, &s3) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t32, transitionCounter++, &s3, &s2) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t2bb1aa, transitionCounter++, &s2bb, &s1aa) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t2bb2a, transitionCounter++, &s2bb, &s2a) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t2a2ba, transitionCounter++, &s2a, &s2ba) != SM_OK) {
    return 1;
  }
  if(StateMachine_AddTransition_(&TestStateMachine, &t2ba2bb, transitionCounter++, &s2ba, &s2bb) != SM_OK) {
    return 1;
  }

  StateMachine_Start_(&TestStateMachine);

  // Registering state machine events
  fStateMachine_RegisterTransitionOccuredEvent(&TestStateMachine, TransitionOccuredEvent);
  fStateMachine_RegisterTransitionRejectedEvent(&TestStateMachine, TransitionRejectedEvent);
  fStateMachine_RegisterStateEnteredEvent(&TestStateMachine, StateEnteredEvent);
  fStateMachine_RegisterStateDoneEvent(&TestStateMachine, StateDoneEvent);
  fStateMachine_RegisterStateExitedEvent(&TestStateMachine, StateExitedEvent);
  fStateMachine_RegisterTransitionActionDoneEvent(&TestStateMachine, TransitionActionExecutedEvent);
  fStateMachine_RegisterTransitionEvtCheckingEvent(&TestStateMachine, TransitionEvtCheckingEvent);
  fStateMachine_RegisterTransitionGuardCheckingEvent(&TestStateMachine, TransitionGuardCheckingEvent);
  fStateMachine_RegisterExecutionErrorOccuredEvent(&TestStateMachine, ExecutionErrorOccuredEvent);

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {
  
  RUN_EVERY_MS_(StateMachineRt, 100) {

    uint8_t smEvent = 0; // TODO: Events can be passed to state machine through this!
    
    fStateMachine_Step(&TestStateMachine, &smEvent);
    
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
 * @brief Transition occured event callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void TransitionOccuredEvent(void *sender, sTransitionEventArgs *e) {
  
}

/**
 * @brief Transition rejected event callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void TransitionRejectedEvent(void *sender, sTransitionEventArgs *e) {

}

/**
 * @brief Transition action function executed event callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void TransitionActionExecutedEvent(void *sender, sTransitionEventArgs *e) {

}

/**
 * @brief State entered event callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void StateEnteredEvent(void *sender, sStateEventArgs *e) {

}

/**
 * @brief State done event callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void StateDoneEvent(void *sender, sStateEventArgs *e) {

}

/**
 * @brief State exited event callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void StateExitedEvent(void *sender, sStateEventArgs *e) {

}

/**
 * @brief Transition event checking callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void TransitionEvtCheckingEvent(void *sender, sTransitionCheckingArgs *e) {

}

/**
 * @brief Transition guard condition checking callback.
 * 
 * @param sender Pointer to state machine that is the sender of this event.
 * @param e Pointer to the event arguments.
 */
static void TransitionGuardCheckingEvent(void *sender, sTransitionCheckingArgs *e) {

}

/**
 * @brief State machine error occured event.
 * 
 * @param sender Pointer to state machine object.
 * @param e Pointer to the event params.
 */
static void ExecutionErrorOccuredEvent(void *sender, sExecutionErrorArgs *e) {

}

/**
 * @brief Action function of the initial transition in state machine.
 * 
 */
STATE_MACHINE_INITIAL_TRANSITION_ACTION_(TestStateMachine) {

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
 * @brief Entry function of the s1a.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s1a, void *sender) {

}

/**
 * @brief Do function of the s1a.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s1a, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s1a.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s1a, void *sender) {

}

/**
 * @brief Entry function of the s1b.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s1b, void *sender) {

}

/**
 * @brief Do function of the s1b.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s1b, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s1b.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s1b, void *sender) {

}

/**
 * @brief Entry function of the s1c.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s1c, void *sender) {

}

/**
 * @brief Do function of the s1c.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s1c, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s1c.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s1c, void *sender) {

}

/**
 * @brief Entry function of the s2a.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s2a, void *sender) {

}

/**
 * @brief Do function of the s2a.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s2a, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s2b.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s2a, void *sender) {

}

/**
 * @brief Entry function of the s2b.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s2b, void *sender) {

}

/**
 * @brief Do function of the s2b.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s2b, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s2b.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s2b, void *sender) {

}

/**
 * @brief Entry function of the s3a.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s3a, void *sender) {

}

/**
 * @brief Do function of the s3a.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s3a, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s3a.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s3a, void *sender) {

}

/**
 * @brief Entry function of the s1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s1aa, void *sender) {

}

/**
 * @brief Do function of the s1aa.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s1aa, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s1aa, void *sender) {

}

/**
 * @brief Entry function of the s1ab.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s1ab, void *sender) {

}

/**
 * @brief Do function of the s1ab.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s1ab, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s1ab.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s1ab, void *sender) {

}

/**
 * @brief Entry function of the s2ba.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s2ba, void *sender) {

}

/**
 * @brief Do function of the s2ba.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s2ba, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s2ba.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s2ba, void *sender) {

}

/**
 * @brief Entry function of the s2bb.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s2bb, void *sender) {

}

/**
 * @brief Do function of the s2bb.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s2bb, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s2bb.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s2bb, void *sender) {

}

/**
 * @brief Entry function of the s3aa.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s3aa, void *sender) {

}

/**
 * @brief Do function of the s3aa.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s3aa, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s3aa.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s3aa, void *sender) {

}

/**
 * @brief Entry function of the s3aaa.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(s3aaa, void *sender) {

}

/**
 * @brief Do function of the s3aaa.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(s3aaa, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the s3aaa.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(s3aaa, void *sender) {

}

/**
 * @brief Entry function of the st.
 * 
 * @param sender 
 */
STATE_MACHINE_ENTRY_(st, void *sender) {

}

/**
 * @brief Do function of the st.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_DO_(st, void *sender, sStateMachineEvt *evArgs) {

}

/**
 * @brief Exit function of the st.
 * 
 * @param sender 
 */
STATE_MACHINE_EXIT_(st, void *sender) {

}

/**
 * @brief Initial transition action of s1 first child.
 * 
 * @param sender Pointer to s1.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s1, void *sender) {
  
}

/**
 * @brief Initial transition action of s2 first child.
 * 
 * @param sender Pointer to s2.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s2, void *sender) {
  
}

/**
 * @brief Initial transition action of s3 first child.
 * 
 * @param sender Pointer to s3.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s3, void *sender) {
  
}

/**
 * @brief Initial transition action of s1a first child.
 * 
 * @param sender Pointer to s1a.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s1a, void *sender) {
  
}

/**
 * @brief Initial transition action of s2b first child.
 * 
 * @param sender Pointer to s2b.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s2b, void *sender) {
  
}

/**
 * @brief Initial transition action of s3a first child.
 * 
 * @param sender Pointer to s3a.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s3a, void *sender) {
  
}

/**
 * @brief Initial transition action of s3aa first child.
 * 
 * @param sender Pointer to s3aa.
 */
STATE_MACHINE_COMPOSITE_STATE_INITIAL_TRANSITION_(s3aa, void *sender) {
  
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
 * @brief Event function of the transition t1c1b.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1c1b, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1c1b.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1c1b, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1c1b.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1c1b, void *sender) {

}

/**
 * @brief Event function of the transition t1a1c.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1a1c, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1a1c.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1a1c, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1a1c.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1a1c, void *sender) {

}

/**
 * @brief Event function of the transition t1b1a.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1b1a, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1b1a.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1b1a, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1b1a.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1b1a, void *sender) {

}

/**
 * @brief Event function of the transition t1a1aa.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1a1aa, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1a1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1a1aa, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1a1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1a1aa, void *sender) {

}

/**
 * @brief Event function of the transition t1a1a.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1a1a, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1a1a.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1a1a, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1a1a.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1a1a, void *sender) {

}

/**
 * @brief Event function of the transition t1ab1aa.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1ab1aa, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1ab1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1ab1aa, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1ab1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1ab1aa, void *sender) {

}

/**
 * @brief Event function of the transition t1aa1ab.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1aa1ab, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1aa1ab.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1aa1ab, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1aa1ab.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1aa1ab, void *sender) {

}

/**
 * @brief Event function of the transition t1aa1.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1aa1, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1aa1.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1aa1, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1aa1.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1aa1, void *sender) {

}

/**
 * @brief Event function of the transition t1ab1ab.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t1ab1ab, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t1ab1ab.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t1ab1ab, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t1ab1ab.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t1ab1ab, void *sender) {

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
 * @brief Event function of the transition t2bb1aa.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t2bb1aa, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t2bb1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t2bb1aa, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t2bb1aa.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t2bb1aa, void *sender) {

}

/**
 * @brief Event function of the transition t22.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t22, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t22.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t22, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t22.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t22, void *sender) {

}

/**
 * @brief Event function of the transition t2bb2a.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t2bb2a, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t2bb2a.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t2bb2a, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t2bb2a.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t2bb2a, void *sender) {

}

/**
 * @brief Event function of the transition t2a2ba.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t2a2ba, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t2a2ba.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t2a2ba, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t2a2ba.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t2a2ba, void *sender) {

}

/**
 * @brief Event function of the transition t2ba2bb.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t2ba2bb, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t2ba2bb.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t2ba2bb, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t2ba2bb.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t2ba2bb, void *sender) {

}

/**
 * @brief Event function of the transition t32.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t32, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t32.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t32, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t32.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t32, void *sender) {

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
 * @brief Event function of the transition t2t.
 * 
 * @param sender 
 * @param event 
 */
STATE_MACHINE_TRANSITION_EVENT_(t2t, void *sender, sStateMachineEvt *evArgs) {

  return false;
}

/**
 * @brief Guard function of the transition t2t.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_GUARD_(t2t, void *sender) {

  return false;
}

/**
 * @brief Action function of the transition t2t.
 * 
 * @param sender 
 */
STATE_MACHINE_TRANSITION_ACTION_(t2t, void *sender) {

}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

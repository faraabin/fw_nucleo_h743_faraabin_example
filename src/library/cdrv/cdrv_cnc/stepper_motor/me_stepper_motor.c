/**
 ******************************************************************************
 *  @file         me_stepper_motor.c
 *  @brief        ...
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 * DESCRIPTION:
 *
 ******************************************************************************
 * HOW TO USE:
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "me_stepper_motor.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define K_FRQ 10

/* Private macro -------------------------------------------------------------*/
#define TIMER_CLK_ENABLE_(timer_no_)\
	do {\
		switch(timer_no_)\
		{\
			case 1: {\
				__TIM1_CLK_ENABLE();\
				break;\
			}\
			case 2: {\
				__TIM2_CLK_ENABLE();\
				break;\
			}\
			case 3: {\
				__TIM3_CLK_ENABLE();\
				break;\
			}\
			case 4: {\
				__TIM4_CLK_ENABLE();\
				break;\
			}\
			case 5: {\
				__TIM5_CLK_ENABLE();\
				break;\
			}\
			case 6: {\
				__TIM6_CLK_ENABLE();\
				break;\
			}\
			case 7: {\
				__TIM7_CLK_ENABLE();\
				break;\
			}\
			case 8: {\
				__TIM8_CLK_ENABLE();\
				break;\
			}\
		}\
	}while(0)\
	
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t meStepperMotor_Init(sStepperMotor_Obj * const me) {
	
	meUNIT_INIT_START_();
	
	if(me->PinPulse == NULL) {
		return 1;
	}
	
	if(me->PinDirection == NULL) {
		return 1;
	}
	
	if(me->PinEnable == NULL) {
		return 1;
	}
	
	me->PinPulse->u_dir = eGPIO_DIR_OUTPUT;
	me->PinPulse->u_out_type = eGPIO_PUSH_PULL;
	meUNIT_INIT_RET_(meGpio_Init_(me->PinPulse));
	meGpio_Reset_(me->PinPulse);
	
	me->PinDirection->u_dir = eGPIO_DIR_OUTPUT;
	me->PinDirection->u_out_type = eGPIO_PUSH_PULL;
	me->PinDirection->u_invert = me->DirectionInvert;
	meUNIT_INIT_RET_(meGpio_Init_(me->PinDirection));
	meGpio_Reset_(me->PinDirection);
	
	me->PinEnable->u_dir = eGPIO_DIR_OUTPUT;
	me->PinEnable->u_out_type = eGPIO_PUSH_PULL;
	meUNIT_INIT_RET_(meGpio_Init_(me->PinEnable));
	meGpio_Reset_(me->PinEnable);
	
	meStepperMotor_Disable(me);
	
	me->IsInProc = false;
	me->State = eSTEP_MOTOR_STATE_STOP;
	me->PositionPulseQty = 0;
	me->PositionAngle = 0;
	me->_pulseCounter = 0;
	me->_direction = eSTEP_MOTOR_DIR_CW;
	me->_clk = false;
	
	//Timer Init
	TIMER_CLK_ENABLE_(me->TimerNo);
	  
	me->_timerHandle.Instance = me->TimerInstance;
	me->_timerHandle.Init.Prescaler = 0;
	me->_timerHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	me->_timerHandle.Init.Period = 4294967295;
	me->_timerHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	me->_timerHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&(me->_timerHandle)) != HAL_OK) {
		return 1;
	}

	__HAL_TIM_CLEAR_IT(&(me->_timerHandle), TIM_IT_UPDATE);
	
	HAL_NVIC_SetPriority(me->TimerIRQn, 0, 0);
	HAL_NVIC_EnableIRQ(me->TimerIRQn);  

	return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Run(sStepperMotor_Obj * const me) {
	
	__HAL_TIM_CLEAR_IT(&(me->_timerHandle), TIM_IT_UPDATE);
  
	bool cw_limit = false;
	if(me->IsCwLimit != NULL) {
		cw_limit = me->IsCwLimit();
	}
	
	bool ccw_limit = false;
	if(me->IsCcwLimit != NULL) {
		ccw_limit = me->IsCcwLimit();
	}
	
  if(
			(((cw_limit == true) && (me->_direction == eSTEP_MOTOR_DIR_CW)) ||  ((ccw_limit == true) && (me->_direction == eSTEP_MOTOR_DIR_CCW))) &&
			(me->IsInProc == true)) {
		
		if(me->EventCb != NULL) {
			me->EventCb(me, eSTEP_MOTOR_EVENT_LIMIT);
		}
    meStepperMotor_Stop(me);
    return;
  }

	if (me->IsInProc) {
    
		if(me->_clk) {
			meGpio_Set_(me->PinPulse);
    } else {
			meGpio_Reset_(me->PinPulse);
    }
		
    me->_clk = !me->_clk;
		
    if (!me->_clk) {
      
			if(me->_pulseCounter != 0) {
				me->_pulseCounter--;
      }
			if(me->_direction == eSTEP_MOTOR_DIR_CW) {
				me->PositionPulseQty++;
      } else {
				me->PositionPulseQty--;
      }
		} else if(me->_pulseCounter == 0) {
      
      meStepperMotor_Stop(me);
		}
	}
	
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t meStepperMotor_ConfigPulse(sStepperMotor_Obj * const me, int32_t pulseQty, float32_t timeMs) {
	
	if(pulseQty == 0) {
		return 0;
	}
	
	if(pulseQty > 0) {
		me->_direction = eSTEP_MOTOR_DIR_CW;
		meGpio_Set_(me->PinDirection);
	} else { 
		me->_direction = eSTEP_MOTOR_DIR_CCW;
		meGpio_Reset_(me->PinDirection);
		
		pulseQty = -1 * pulseQty;
	}
	
	uint32_t pscValue;
  
  uint32_t f = ((float)pulseQty / (timeMs / 10)) * 1000.0f;
  if(f > (15000 * K_FRQ)) {
    f = 15000 * K_FRQ;	// 15kHz
  }
	
  if (f < K_FRQ) {
    f = K_FRQ;			// 1Hz
  }

  pscValue = 1;

  uint32_t arrValue = (SystemCoreClock / 2 * K_FRQ) / f; // (1 falling adge on 2 IRQ)
  while ((arrValue & 0xffff0000) != 0) {
    pscValue = pscValue << 1;
    arrValue = arrValue >> 1;
  }
  pscValue--;
  
  me->_pulseCounter = (uint32_t)pulseQty;
  me->_clk = true;
  
  me->_timerHandle.Instance->PSC = pscValue;
  __HAL_TIM_SetAutoreload(&(me->_timerHandle), arrValue);
	
	return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t meStepperMotor_ConfigPulseFreq(sStepperMotor_Obj * const me, int32_t pulseQty, float32_t freq) {
	
	float32_t timeMs = fabs(((float32_t)pulseQty / freq) * 1000.0f);
	
	return meStepperMotor_ConfigPulse(me, pulseQty, timeMs);
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t meStepperMotor_ConfigAngle(sStepperMotor_Obj * const me, float32_t angle, float32_t timeMs) {
	
	int32_t pulseQty = (int32_t)(angle * (float)me->PulsePerRound / 360.0f);
	
	return meStepperMotor_ConfigPulse(me, pulseQty, timeMs);
	
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Start(sStepperMotor_Obj * const me) {
	
	if(me->_pulseCounter == 0) {
		return;
	}
	
	me->IsInProc = true;
	
	HAL_TIM_Base_Start_IT(&(me->_timerHandle));
  
	me->State = eSTEP_MOTOR_STATE_RUN;
	
	if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_START);
	}	
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Stop(sStepperMotor_Obj * const me) {
	
	me->_pulseCounter = 0;
	
	HAL_TIM_Base_Stop_IT(&(me->_timerHandle));
	me->IsInProc = false;
	
	me->State = eSTEP_MOTOR_STATE_STOP;
      
  if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_STOP);
	}
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Pause(sStepperMotor_Obj * const me) {
	
	HAL_TIM_Base_Stop_IT(&(me->_timerHandle));
	
	me->State = eSTEP_MOTOR_STATE_PAUSE;
	
	if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_PAUSE);
	}
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Resume(sStepperMotor_Obj * const me) {
	
	HAL_TIM_Base_Start_IT(&(me->_timerHandle));
	
	me->State = eSTEP_MOTOR_STATE_RUN;
	
	if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_RESUME);
	}
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Enable(sStepperMotor_Obj * const me) {
	
	meGpio_Reset_(me->PinEnable);
	
	if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_ENABLE);
	}
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_Disable(sStepperMotor_Obj * const me) {
	
	meGpio_Set_(me->PinEnable);
	
	if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_DISABLE);
	}
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
void meStepperMotor_SetZero(sStepperMotor_Obj * const me) {
	
	me->PositionPulseQty = 0;
	me->PositionAngle = 0;
	
	if(me->EventCb != NULL) {
		me->EventCb(me, eSTEP_MOTOR_EVENT_SET_ZERO);
	}
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t meStepperMotor_StartMoveCw(sStepperMotor_Obj * const me, float32_t freq) {
	
	if(meStepperMotor_ConfigPulseFreq(me, 1000000, freq) != 0) {
		return 1;
	}
	
	meStepperMotor_Start(me);
	
	return 0;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
uint8_t meStepperMotor_StartMoveCcw(sStepperMotor_Obj * const me, float32_t freq) {
	
	if(meStepperMotor_ConfigPulseFreq(me, -1000000, freq) != 0) {
		return 1;
	}
	
	meStepperMotor_Start(me);
	
	return 0;
}

/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

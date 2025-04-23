/**
 ******************************************************************************
 *  @file         me_stepper_motor_ocmd.c
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
#include "me_stepper_motor_ocmd.h"

#include "me_stepper_motor.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sStepperMotor_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Status,
"type cmd help here") {
	
	mePRINTF_("\r\nDirection Invert: %s", (me->DirectionInvert) ? "True" : "False");
	mePRINTF_("\r\nPulsePerRound: %u", me->PulsePerRound);
	switch(me->State) {
		
		case eSTEP_MOTOR_STATE_STOP: {
			mePRINTF_("\r\nStatus: STOP");
			break;
		}
		case eSTEP_MOTOR_STATE_RUN: {
			mePRINTF_("\r\nStatus: RUN");
			break;
		}
		case eSTEP_MOTOR_STATE_PAUSE: {
			mePRINTF_("\r\nStatus: PAUSE");
			break;
		}		
	}
	mePRINTF_("\r\nPosition: %i, %f", me->PositionPulseQty, me->PositionAngle);
	if(me->IsCwLimit != NULL) {
		mePRINTF_("\r\nCW Limit: %s", (me->IsCwLimit()) ? "True" : "False");
	}
	if(me->IsCcwLimit != NULL) {
		mePRINTF_("\r\nCCW Limit: %s", (me->IsCcwLimit()) ? "True" : "False");
	}
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, ConfigPulse,
"type cmd help here") {
	
	int32_t pulseQty;
	float32_t timeMs;
	
	meCONSOLE_GET_PAR_(2, "%i %f", &pulseQty, &timeMs);
	
	if(meStepperMotor_ConfigPulse(me, pulseQty, timeMs) != 0) {
		
		mePRINTF_ERROR_("\r\nError");
		
	}
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, ConfigPulseFreq,
"type cmd help here") {
	
	int32_t pulseQty;
	float32_t freq;
	
	meCONSOLE_GET_PAR_(2, "%i %f", &pulseQty, &freq);
	
	if(meStepperMotor_ConfigPulseFreq(me, pulseQty, freq) != 0) {
		
		mePRINTF_ERROR_("\r\nError");
		
	}
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, ConfigAngle,
"type cmd help here") {
	
	float32_t angle;
	float32_t timeMs;
	
	meCONSOLE_GET_PAR_(2, "%f %f", &angle, &timeMs);
	
	if(meStepperMotor_ConfigAngle(me, angle, timeMs) != 0) {
		
		mePRINTF_ERROR_("\r\nError");
		
	}
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Start,
"type cmd help here") {
	
	meStepperMotor_Start(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Stop,
"type cmd help here") {
	
	meStepperMotor_Stop(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Pause,
"type cmd help here") {
	
	meStepperMotor_Pause(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Resume,
"type cmd help here") {
	
	meStepperMotor_Resume(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Enable,
"type cmd help here") {
	
	meStepperMotor_Enable(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, Disable,
"type cmd help here") {
	
	meStepperMotor_Disable(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, SetZero,
"type cmd help here") {
	
	meStepperMotor_SetZero(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, StartMoveCw,
"type cmd help here") {
	
	float32_t freq;
	
	meCONSOLE_GET_PAR_(1, "%f", &freq);
	
	if(meStepperMotor_StartMoveCw(me, freq) != 0) {
		
		mePRINTF_ERROR_("\r\nError");
		
	}
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(me_stepper_motor, StartMoveCcw,
"type cmd help here") {
	
	float32_t freq;
	
	meCONSOLE_GET_PAR_(1, "%f", &freq);
	
	if(meStepperMotor_StartMoveCcw(me, freq) != 0) {
		
		mePRINTF_ERROR_("\r\nError");
		
	}
  
	meCONSOLE_END_;
}

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
meCONSOLE_GROUP_(me_stepper_motor,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(me_stepper_motor, Status, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, ConfigPulse, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, ConfigPulseFreq, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, ConfigAngle, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, Start, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, Stop, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, Pause, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, Resume, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, Enable, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, Disable, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, SetZero, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, StartMoveCw, 0);
	meCONSOLE_ADD_CMD_(me_stepper_motor, StartMoveCcw, 0);
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

/**
 ******************************************************************************
 *  @file         me_stepper_motor.h
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
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __me_stepper_motor_H
#define __me_stepper_motor_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "library\faraabin\faraabin.h"
#include "stm32h7xx.h"
  
/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
/**
  * @brief
  */
typedef enum {
	
	eSTEP_MOTOR_STATE_STOP = 0,
	eSTEP_MOTOR_STATE_RUN,
	eSTEP_MOTOR_STATE_PAUSE,
	
}eSteppMotorState;

/**
  * @brief
  */
typedef enum {
	
	eSTEP_MOTOR_EVENT_STOP = 0,
	eSTEP_MOTOR_EVENT_LIMIT,
	eSTEP_MOTOR_EVENT_PAUSE,
	eSTEP_MOTOR_EVENT_RESUME,
	eSTEP_MOTOR_EVENT_START,
	eSTEP_MOTOR_EVENT_ENABLE,
	eSTEP_MOTOR_EVENT_DISABLE,
	eSTEP_MOTOR_EVENT_SET_ZERO,
	
}eSteppMotorEvent;

/**
  * @brief
  */
typedef enum {
	
	eSTEP_MOTOR_DIR_CW = 0,
	eSTEP_MOTOR_DIR_CCW,
	
}eSteppMotorDirection;

/**
  * @brief
  */
typedef struct {
	
	char *Name;
	
	uint32_t PulsePerRound;
	
	bool DirectionInvert;
	
	eSteppMotorState State;
	
	TysGpio_Obj *PinPulse;
	
	TysGpio_Obj *PinDirection;
	
	TysGpio_Obj *PinEnable;
	
	bool(*IsCwLimit)(void);
	
	bool(*IsCcwLimit)(void);
	
	void(*EventCb)(void *me, eSteppMotorEvent event);
	
	uint8_t TimerNo;
	
	TIM_TypeDef *TimerInstance;
	
	TIM_HandleTypeDef _timerHandle;
	
	IRQn_Type TimerIRQn;
	
	int32_t PositionPulseQty;
	
	float32_t PositionAngle;
	
	uint32_t _pulseCounter;
	
	eSteppMotorDirection _direction;
	
	bool IsInProc;
	
	bool _clk;
	                               
}sStepperMotor_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t meStepperMotor_Init(sStepperMotor_Obj * const me);
void meStepperMotor_Run(sStepperMotor_Obj * const me);
uint8_t meStepperMotor_ConfigPulse(sStepperMotor_Obj * const me, int32_t pulseQty, float32_t timeMs);
uint8_t meStepperMotor_ConfigPulseFreq(sStepperMotor_Obj * const me, int32_t pulseQty, float32_t freq);
uint8_t meStepperMotor_ConfigAngle(sStepperMotor_Obj * const me, float32_t angle, float32_t timeMs);
void meStepperMotor_Start(sStepperMotor_Obj * const me);
void meStepperMotor_Stop(sStepperMotor_Obj * const me);
void meStepperMotor_Pause(sStepperMotor_Obj * const me);
void meStepperMotor_Resume(sStepperMotor_Obj * const me);
void meStepperMotor_Enable(sStepperMotor_Obj * const me);
void meStepperMotor_Disable(sStepperMotor_Obj * const me);
void meStepperMotor_SetZero(sStepperMotor_Obj * const me);
uint8_t meStepperMotor_StartMoveCw(sStepperMotor_Obj * const me, float32_t freq);
uint8_t meStepperMotor_StartMoveCcw(sStepperMotor_Obj * const me, float32_t freq);

/* Extern functions ----------------------------------------------------------*/
/* Extern Object or Variable -------------------------------------------------*/

/**End of Group_Name
  * @}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

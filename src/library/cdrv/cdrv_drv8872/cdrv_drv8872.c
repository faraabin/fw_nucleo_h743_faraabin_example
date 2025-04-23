/**
 ******************************************************************************
 *  @file         cdrv_drv8872.c
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
#include "cdrv_drv8872.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DO_TOGGLE_TIME_us 2000

/* Private macro -------------------------------------------------------------*/
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
uint8_t CdrvDrv8872_Init(TysCdrvDrv8872_Obj * const me) {
  
	me->init = false;

	if((me->u_do_pin1 == NULL) |
		 (me->u_do_pin2 == NULL)) {
			 return 1;
	}

	me->u_do_pin1->u_dir = eGPIO_DIR_OUTPUT;
	me->u_do_pin1->u_out_type = eGPIO_PUSH_PULL;
	meGpio_Init_(me->u_do_pin1);
	meGpio_Set_(me->u_do_pin1);
	me->state_do1 = false;

	me->u_do_pin2->u_dir = eGPIO_DIR_OUTPUT;
	me->u_do_pin2->u_out_type = eGPIO_PUSH_PULL;
	meGpio_Init_(me->u_do_pin2);
	meGpio_Set_(me->u_do_pin2);
	me->state_do2 = false;

	me->first_toggle_init = true;

	me->init = true;
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
void CdrvDrv8872_Run(TysCdrvDrv8872_Obj * const me) {
  if(me->init == false) {
    return;
  }
  
	if((me->state_do1 == true) && (me->state_do2 == true)) {
		
		if(me->first_toggle_init == true) {
			me->first_toggle_init = false;
			
			meGpio_Set_(me->u_do_pin1);
			meGpio_Reset_(me->u_do_pin2);
			
		} else {
			meRUN_EVERY_us_(gpio_toggle, DO_TOGGLE_TIME_us) {
				meGpio_Toggle_(me->u_do_pin1);
				meGpio_Toggle_(me->u_do_pin2);
				meRUN_EVERY_END_;
			}
		}
		
	} else if((me->state_do1 == true) && (me->state_do2 == false)) {
		me->first_toggle_init = true;
		meGpio_Set_(me->u_do_pin1);
		meGpio_Reset_(me->u_do_pin2);
	} else if((me->state_do1 == false) && (me->state_do2 == true)) {
		me->first_toggle_init = true;
		meGpio_Reset_(me->u_do_pin1);
		meGpio_Set_(me->u_do_pin2);
	} else if((me->state_do1 == false) && (me->state_do2 == false)) {
		me->first_toggle_init = true;
		meGpio_Set_(me->u_do_pin1);
		meGpio_Set_(me->u_do_pin2);
	}
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDrv8872_SetState(TysCdrvDrv8872_Obj * const me, TyeDrv8872_DoNumber do_num, bool state) {
  
  if(me->init == false) {
    return 1;
  }
	
	switch(do_num) {
		
		case eDO_NUM_BOTH:
		{
			me->state_do1 = state;
			me->state_do2 = state;
			break;
		}
		
		case eDO_NUM_1:
		{
			me->state_do1 = state;
			break;
		}
		
		case eDO_NUM_2:
		{
			me->state_do2 = state;
			break;
		}
		
		default:
			return 1;
	}
  
  return 0;
}

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

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

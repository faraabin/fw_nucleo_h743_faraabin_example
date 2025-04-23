/**
 ******************************************************************************
 *  @file         cdrv_rm3100_ocmd.c
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
#include "cdrv_rm3100_ocmd.h"

#include "cdrv_rm3100.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(sCdrvRm3100_Obj);

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
meCONSOLE_CMD_(cdrv_rm3100, READ,
"type cmd help here") {
  
  meCONSOLE_LOOP_PAR_() {
		
		if(fCdrvRm3100_Update(me) != 0) {
			
			mePRINTF_("\r\nERROR");
			
		} else {
			
			//display results
			mePRINTF_("\r\nx/y/z(Count) : %i, %i, %i", me->x_Count, me->y_Count, me->z_Count);
			mePRINTF_("\r\nx/y/z(uT) : %f, %f, %f", me->x_uT, me->y_uT, me->z_uT);
			mePRINTF_("\r\nMagnitude(uT): %f", me->uT);
			
		}
		
		meCONSOLE_LOOP_PAR_END_;
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
meCONSOLE_GROUP_(cdrv_rm3100,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_rm3100, READ, 0);
  
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

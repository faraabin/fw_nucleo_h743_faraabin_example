/**
 ******************************************************************************
 *  @file         cdrv_drv8872_ocmd.c
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
#include "cdrv_drv8872_ocmd.h"

#include "cdrv_drv8872.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvDrv8872_Obj);

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
meCONSOLE_CMD_(cdrv_drv8872, SET_DO,
"type cmd help here") {
	
	uint32_t do_number;
  
  meCONSOLE_GET_PAR_(1, "%u", &do_number);
	CdrvDrv8872_SetState(me, (TyeDrv8872_DoNumber)do_number, true);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(cdrv_drv8872, RESET_DO,
"type cmd help here") {
  
  uint32_t do_number;
  
  meCONSOLE_GET_PAR_(1, "%u", &do_number);
	CdrvDrv8872_SetState(me, (TyeDrv8872_DoNumber)do_number, false);
  
	meCONSOLE_END_;
}

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief Initialize Module.
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(cdrv_drv8872,
"type cmd help here") {
  
	meCONSOLE_ADD_CMD_(cdrv_drv8872, SET_DO, 0);
  meCONSOLE_ADD_CMD_(cdrv_drv8872, RESET_DO, 0);
  
	meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

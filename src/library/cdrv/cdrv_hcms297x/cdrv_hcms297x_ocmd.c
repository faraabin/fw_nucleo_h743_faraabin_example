/**
 ******************************************************************************
 *  @file         cdrv_hcms297x_ocmd.c
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
#include "cdrv_hcms297x_ocmd.h"

#include "cdrv_hcms297x.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvHcms297x_Obj);

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
meCONSOLE_CMD_(cdrv_hcms297x, BL_ENABLE,
"type cmd help here") {
  
  CdrvHcms297x_BlankEnable(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_hcms297x, BL_DISABLE,
"type cmd help here") {
  
  CdrvHcms297x_BlankDisable(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_hcms297x, SET_CONTRAST,
"type cmd help here") {
  
  int contrast;
  meCONSOLE_GET_PAR_(1, "%u", &contrast);
  
  CdrvHcms297x_SetContrast(me, contrast);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_hcms297x, CLEAR,
"type cmd help here") {
  
  CdrvHcms297x_Clear(me);
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_hcms297x, PRINT,
"type cmd help here") {
  
  char msg[100];
  meCONSOLE_GET_PAR_(1, "%s", msg);
  
  if(CdrvHcms297x_Print(me, (uint8_t*)msg, strlen(msg), 0) != 0) {
    mePRINTF_("\r\nERROR");
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
meCONSOLE_GROUP_(cdrv_hcms297x,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_hcms297x, BL_ENABLE, 0);
  meCONSOLE_ADD_CMD_(cdrv_hcms297x, BL_DISABLE, 0);
  meCONSOLE_ADD_CMD_(cdrv_hcms297x, SET_CONTRAST, 0);
  meCONSOLE_ADD_CMD_(cdrv_hcms297x, CLEAR, 0);
  meCONSOLE_ADD_CMD_(cdrv_hcms297x, PRINT, 0);
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

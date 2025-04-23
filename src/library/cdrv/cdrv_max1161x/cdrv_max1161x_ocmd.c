/**
 ******************************************************************************
 *  @file         cdrv_max1161x_ocmd.c
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
#include "cdrv_max1161x_ocmd.h"

#include "cdrv_max1161x.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvMax1161x_Obj);

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
meCONSOLE_CMD_(cdrv_max1161x, SCAN_ROW,
"type cmd help here") {
  
  uint16_t value[8];
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvMax1161x_ScanRow(me, value) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      mePRINTF_("\r\n%7u, %7u, %7u, %7u, %7u, %7u, %7u, %7u", 
      value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);
    }
    
    meCONSOLE_LOOP_PAR_END_;
  }

	meCONSOLE_END_;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
meCONSOLE_CMD_(cdrv_max1161x, SCAN,
"type cmd help here") {
  
  float value[8];
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvMax1161x_Scan(me, value) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      mePRINTF_("\r\n%3.2f, %3.2f, %3.2f, %3.2f, %3.2f, %3.2f, %3.2f, %3.2f", 
      value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7]);
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
meCONSOLE_GROUP_(cdrv_max1161x,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_max1161x, SCAN_ROW, 0);
  meCONSOLE_ADD_CMD_(cdrv_max1161x, SCAN, 0);
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

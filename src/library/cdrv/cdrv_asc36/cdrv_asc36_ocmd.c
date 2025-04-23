/**
 ******************************************************************************
 *  @file         cdrv_asc36_ocmd.c
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
#include "cdrv_asc36_ocmd.h"

#include "cdrv_asc36.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvAsc36_Obj);

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
meCONSOLE_CMD_(cdrv_asc36, READ,
"type cmd help here") {
  
  meCONSOLE_LOOP_PAR_() {
    
    meTICK_();
    uint8_t res = CdrvAsc36_Update(me);
    float elapsed = meTOCK_();
    if(res != 0) {
      mePRINTF_("\r\n(%f us)ERROR", elapsed);
    } else {
      mePRINTF_("\r\n(%f us)Encoder Value : %u, %f", elapsed, me->u_value_raw, me->u_value_degree);
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
meCONSOLE_CMD_(cdrv_asc36, ZERO,
"type cmd help here") {
  
  int zero_value;
  
  meCONSOLE_GET_PAR_(1, "%u", &zero_value);

  if(CdrvAsc36_SetZero(me, (uint16_t)zero_value) != 0) {
    mePRINTF_("\r\nERROR");
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(cdrv_asc36, DIR_CW,
"type cmd help here") {
  
  if(CdrvAsc36_SetDirection(me, eASC36_DIRECTION_CW) != 0) {
    mePRINTF_("\r\nERROR");
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(cdrv_asc36, DIR_CCW,
"type cmd help here") {
  
  if(CdrvAsc36_SetDirection(me, eASC36_DIRECTION_CCW) != 0) {
    mePRINTF_("\r\nERROR");
  }
  
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
meCONSOLE_GROUP_(cdrv_asc36,
"type cmd help here") {
  
	meCONSOLE_ADD_CMD_(cdrv_asc36, READ, 0);
  meCONSOLE_ADD_CMD_(cdrv_asc36, ZERO, 0);
  meCONSOLE_ADD_CMD_(cdrv_asc36, DIR_CW, 0);
  meCONSOLE_ADD_CMD_(cdrv_asc36, DIR_CCW, 0);
  
	meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

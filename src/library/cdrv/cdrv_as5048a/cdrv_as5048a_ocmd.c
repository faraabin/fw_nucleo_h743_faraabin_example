/**
 ******************************************************************************
 *  @file         cdrv_as5048a_ocmd.c
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
#include "cdrv_as5048a_ocmd.h"

#include "cdrv_as5048a.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvAs5048a_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

float enc_value;
meTRACE_OBJECT_DEFINE_(enc_value_obj);
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
meCONSOLE_CMD_(cdrv_as5048a, GET_RAW_ROTATION,
"type cmd help here") {
  
  uint16_t val;
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvAs5048a_GetRawRotation(me, &val) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      //mePRINTF_("\r\nRawRotation = %u", val);
      enc_value = (float)val;
      //meTRACE_VAR_se(enc_value_obj, sizeof(enc_value));
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
meCONSOLE_CMD_(cdrv_as5048a, GET_ROTATION,
"type cmd help here") {
  
  int16_t val;
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvAs5048a_GetRotation(me, &val) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      //mePRINTF_("\r\nRotation = %u", val);
      enc_value = val;
      //meTRACE_VAR_(enc_value_obj, sizeof(enc_value));
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
meCONSOLE_CMD_(cdrv_as5048a, GET_ROTATION_DEGREE,
"type cmd help here") {
  
  //double val;
  
  meCONSOLE_LOOP_PAR_() {
    
//    if(CdrvAs5048a_GetRotationInDegrees(me, &val) != 0) {
//      mePRINTF_("\r\nERROR");
//    } else {
//      //mePRINTF_("\r\nRotation = %f", val);
//      enc_value = val;
//      meTRACE_VAR_(enc_value_obj, sizeof(enc_value));
//    }
    
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
meCONSOLE_CMD_(cdrv_as5048a, GET_ROTATION_RADIAN,
"type cmd help here") {
  
  double val;
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvAs5048a_GetRotationInRadians(me, &val) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      mePRINTF_("\r\nRotation = %f", val);
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
meCONSOLE_CMD_(cdrv_as5048a, SET_ZERO,
"type cmd help here") {
  
  uint16_t position;
  
  if(CdrvAs5048a_GetRawRotation(me, &position) != 0) {
    mePRINTF_("\r\nERROR");
  } else {
    me->u_position = position;
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
meCONSOLE_GROUP_(cdrv_as5048a,
"type cmd help here") {
  
  //meTRACE_DICT_VAR_(enc_value_obj, float32_t, enc_value, 1, true);

	meCONSOLE_ADD_CMD_(cdrv_as5048a, GET_RAW_ROTATION, 0);
  meCONSOLE_ADD_CMD_(cdrv_as5048a, GET_ROTATION, 0);
  meCONSOLE_ADD_CMD_(cdrv_as5048a, GET_ROTATION_DEGREE, 0);
  meCONSOLE_ADD_CMD_(cdrv_as5048a, GET_ROTATION_RADIAN, 0);
  meCONSOLE_ADD_CMD_(cdrv_as5048a, SET_ZERO, 0);
  
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

/**
 ******************************************************************************
 *  @file         cdrv_ad53x6_ocmd.c
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
#include "cdrv_ad53x6_ocmd.h"

#include "cdrv_ad53x6.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvAd53x6_Obj);

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
meCONSOLE_CMD_(cdrv_ad53x6, WRITE_ROW,
"type cmd help here") {
  
  int ch, value;
  
  meCONSOLE_GET_PAR_(2, "%u %u", &ch, &value);
  
  if(CdrvAd53x6_WriteRow(me, (TyeCdrvAd53x6_ChannelId)ch, value) != 0) {
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
meCONSOLE_CMD_(cdrv_ad53x6, WRITE,
"type cmd help here") {
  
  int ch;
  float value;
  
  meCONSOLE_GET_PAR_(2, "%u %f", &ch, &value);
  
  if(CdrvAd53x6_Write(me, (TyeCdrvAd53x6_ChannelId)ch, value) != 0) {
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
meCONSOLE_CMD_(cdrv_ad53x6, READ_ALL_ROW,
"type cmd help here") {
  
  uint16_t value[4];
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvAd53x6_ReadRowAll(me, value) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      mePRINTF_("\r\n%7u, %7u, %7u, %7u", value[0], value[1], value[2], value[3]);
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
meCONSOLE_CMD_(cdrv_ad53x6, READ_ALL,
"type cmd help here") {
  
  float value[4];
  
  meCONSOLE_LOOP_PAR_() {
    
    if(CdrvAd53x6_ReadAll(me, value) != 0) {
      mePRINTF_("\r\nERROR");
    } else {
      mePRINTF_("\r\n%7.3f, %7.3f, %7.3f, %7.3f", value[0], value[1], value[2], value[3]);
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
meCONSOLE_CMD_(cdrv_ad53x6, CLEAR_ALL,
"type cmd help here") {
  
  if(CdrvAd53x6_ClearAll(me) != 0) {
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
meCONSOLE_GROUP_(cdrv_ad53x6,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_ad53x6, WRITE_ROW, 0);
  meCONSOLE_ADD_CMD_(cdrv_ad53x6, WRITE, 0);
  meCONSOLE_ADD_CMD_(cdrv_ad53x6, READ_ALL_ROW, 0);
  meCONSOLE_ADD_CMD_(cdrv_ad53x6, READ_ALL, 0);
  meCONSOLE_ADD_CMD_(cdrv_ad53x6, CLEAR_ALL, 0);
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

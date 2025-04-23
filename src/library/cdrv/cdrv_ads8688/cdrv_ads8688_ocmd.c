/**
 ******************************************************************************
 *  @file         cdrv_ads8688_ocmd.c
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
#include "cdrv_ads8688_ocmd.h"

#include "cdrv_ads8688.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvAds8688_Obj);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
uint16_t data[40];

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
meCONSOLE_CMD_(cdrv_ads8688, READ,
"type cmd help here") {
  
  meCONSOLE_LOOP_(10) {
    
    CdrvAds8688_Read(me, data);
    
    meTRACE_VAR_SEND_NO_FILTER_(data, sizeof(data));
    
//    mePRINTF_("\r\nDATA : %u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", 
//    data[0],
//    data[1],
//    data[2],
//    data[3],
//    data[4],
//    data[5],
//    data[6],
//    data[7],
//    data[8],
//    data[9],
//    data[10],
//    data[11],
//    data[12],
//    data[13],
//    data[14],
//    data[15]);
    
    meCONSOLE_LOOP_END_;
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
meCONSOLE_GROUP_(cdrv_ads8688,
"type cmd help here") {

	meCONSOLE_ADD_CMD_(cdrv_ads8688, READ, 0);
  
  meTRACE_DICT_VAR_(uint16_t, data, 40);
	
  meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

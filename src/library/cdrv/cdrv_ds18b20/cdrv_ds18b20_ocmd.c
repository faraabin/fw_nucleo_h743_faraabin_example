/**
 ******************************************************************************
 *  @file         cdrv_ds18b20_ocmd.c
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
#include "cdrv_ds18b20_ocmd.h"

#include "cdrv_ds18b20.h"

#include "library\chrono\me_chrono.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(TysCdrvDS18B20_Obj);

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
  * @brief Command to Read Memory Map from User Requested Address.
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(cdrv_ds18b20, READ,
"type cmd help here") {
  
  TysChrono_Obj timer;
  float value;
  
  meCONSOLE_LOOP_PAR_() {
    
    CdrvDS18B20_StartAll(me->one_wire); 
    while(CdrvDS18B20_IsAllDone(me->one_wire) == false){}
    meChrono_Start(&timer);
    uint8_t res = CdrvDS18B20_Read(me, &value);
    uint32_t elapsed = meChrono_us_Elapsed(&timer);
    
    if(res == 0) {
      mePRINTF_("\n(%lu us)temp: %.2f", elapsed, value);
    } else {
      mePRINTF_("\n(%lu us)ERROR", elapsed);
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
  * @brief Initialize Module.
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(cdrv_ds18b20,
"type cmd help here") {
  
	meCONSOLE_ADD_CMD_(cdrv_ds18b20, READ, 0);
  
	meCONSOLE_END_;
}

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

/**
 ******************************************************************************
 *  @file         cdrv_drv8872.h
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
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_drv8872_H
#define __cdrv_drv8872_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
/**
  * @brief
  */
typedef enum {
  
  eDO_NUM_BOTH = 0,
  eDO_NUM_1 = 1,
  eDO_NUM_2 = 2,
  
}TyeDrv8872_DoNumber;

/**
  * @brief
  */
typedef struct {
  
  bool init;   /*!< Specifies the ---.
               This parameter can be a value of @ref ---
               @note . */
  
  TysGpio_Obj *u_do_pin1; /*!< Specifies the ---.
                This parameter can be a value of @ref ---
                @note . */
  
  TysGpio_Obj *u_do_pin2; /*!< Specifies the ---.
                This parameter can be a value of @ref ---
                @note . */
	
  bool state_do1; /*!< Specifies the ---.
                This parameter can be a value of @ref ---
                @note . */
  
  bool state_do2; /*!< Specifies the ---.
                This parameter can be a value of @ref ---
                @note . */
	
	bool first_toggle_init;/*!< Specifies the ---.
                This parameter can be a value of @ref ---
                @note . */
	
}TysCdrvDrv8872_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvDrv8872_Init(TysCdrvDrv8872_Obj * const me);
void CdrvDrv8872_Run(TysCdrvDrv8872_Obj * const me);

uint8_t CdrvDrv8872_SetState(TysCdrvDrv8872_Obj * const me, TyeDrv8872_DoNumber do_num, bool state);

/* Extern functions ----------------------------------------------------------*/
/* Extern Object or Variable -------------------------------------------------*/

/**End of Group_Name
  * @}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

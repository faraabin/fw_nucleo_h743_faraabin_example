/**
 ******************************************************************************
 *  @file         cdrv_as5048a.h
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
#ifndef __cdrv_as5048a_H
#define __cdrv_as5048a_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"
  
#include "library\chrono\me_chrono.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
/**
  * @brief
  */
typedef struct {
  INHERITE_(TysObj)              /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysSpi_Obj *u_spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  bool errorFlag;
	bool ocfFlag; // Avoid printing OCF flag everytime
	uint16_t u_position;
	
}TysCdrvAs5048a_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvAs5048a_Init(TysCdrvAs5048a_Obj * const me);

uint8_t CdrvAs5048a_GetRawRotation(TysCdrvAs5048a_Obj * const me, uint16_t *value);
uint8_t CdrvAs5048a_GetRotation(TysCdrvAs5048a_Obj * const me, int16_t *value);
uint8_t CdrvAs5048a_GetRotationInDegrees(TysCdrvAs5048a_Obj * const me, float *value);
uint8_t CdrvAs5048a_GetRotationInRadians(TysCdrvAs5048a_Obj * const me, double *value);

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

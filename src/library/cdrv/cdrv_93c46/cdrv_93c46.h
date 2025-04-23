/**
 ******************************************************************************
 *  @file         cdrv_93c46.h
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
#ifndef __cdrv_93c46_H
#define __cdrv_93c46_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"
  
#include "library\memory\me_memory_intf.h"
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
typedef enum {
  e93C46_MODE_8BIT = 0,
  e93C46_MODE_16BIT = 1
}TyeCdrv93C46_Mode;

/**
  * @brief
  */
typedef struct {
  INHERITE_(TysObj)              /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TyeCdrv93C46_Mode mode;       /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_wp;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  TysGpio_Obj *u_di;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                             
  TysGpio_Obj *u_do;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  TysGpio_Obj *u_clk;           /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  bool  ew;                     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrv93C46_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t Cdrv93C46_Init(TysCdrv93C46_Obj * const me, TyeCdrv93C46_Mode mode);
TysMemory_Obj* Cdrv93C46_CreatePartirion(TysCdrv93C46_Obj * const me, uint32_t start_addr, uint32_t size);
uint32_t Cdrv93C46_GetSize (TysCdrv93C46_Obj * const me);

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

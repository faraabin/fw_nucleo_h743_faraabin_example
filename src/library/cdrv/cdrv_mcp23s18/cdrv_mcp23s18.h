/**
 ******************************************************************************
 *  @file         cdrv_mcp23s18.h
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
#ifndef __cdrv_mcp23s18_H
#define __cdrv_mcp23s18_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"
  
#include "hal\phal\intf\me_hal_spi_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/

/** 
  * @brief
  */
typedef struct {
	uint8_t pin_no;
  void *parent;
}TysHalGpioPrivate;

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
  
  struct TysPins {
    
    TysGpio_Obj gpa0;
    TysGpio_Obj gpa1;
    TysGpio_Obj gpa2;
    TysGpio_Obj gpa3;
    TysGpio_Obj gpa4;
    TysGpio_Obj gpa5;
    TysGpio_Obj gpa6;
    TysGpio_Obj gpa7;
    
    TysGpio_Obj gpb0;
    TysGpio_Obj gpb1;
    TysGpio_Obj gpb2;
    TysGpio_Obj gpb3;
    TysGpio_Obj gpb4;
    TysGpio_Obj gpb5;
    TysGpio_Obj gpb6;
    TysGpio_Obj gpb7;
    
  }u_pins;
  
  struct TysPinsPrivate {
    
    TysHalGpioPrivate gpa0;
    TysHalGpioPrivate gpa1;
    TysHalGpioPrivate gpa2;
    TysHalGpioPrivate gpa3;
    TysHalGpioPrivate gpa4;
    TysHalGpioPrivate gpa5;
    TysHalGpioPrivate gpa6;
    TysHalGpioPrivate gpa7;
    
    TysHalGpioPrivate gpb0;
    TysHalGpioPrivate gpb1;
    TysHalGpioPrivate gpb2;
    TysHalGpioPrivate gpb3;
    TysHalGpioPrivate gpb4;
    TysHalGpioPrivate gpb5;
    TysHalGpioPrivate gpb6;
    TysHalGpioPrivate gpb7;
    
  }privates;
  
  bool u_online;                /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint16_t write_value;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint16_t read_value;          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint16_t direction;           /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrvMcp23s18_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvMcp23s18_Init(TysCdrvMcp23s18_Obj * const me);
uint8_t CdrvMcp23s18_SyncUpdate(TysCdrvMcp23s18_Obj * const me);

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

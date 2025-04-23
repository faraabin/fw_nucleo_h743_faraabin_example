/**
 ******************************************************************************
 *  @file         cdrv_max7301.h
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
#ifndef __cdrv_max7301_H
#define __cdrv_max7301_H

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
    
    TysGpio_Obj p4;
    TysGpio_Obj p5;
		TysGpio_Obj p6;
		TysGpio_Obj p7;
		TysGpio_Obj p8;
		TysGpio_Obj p9;
		TysGpio_Obj p10;
		TysGpio_Obj p11;
		TysGpio_Obj p12;
		TysGpio_Obj p13;
		TysGpio_Obj p14;
		TysGpio_Obj p15;
		TysGpio_Obj p16;
		TysGpio_Obj p17;
		TysGpio_Obj p18;
		TysGpio_Obj p19;
		TysGpio_Obj p20;
		TysGpio_Obj p21;
		TysGpio_Obj p22;
		TysGpio_Obj p23;
		TysGpio_Obj p24;
		TysGpio_Obj p25;
		TysGpio_Obj p26;
		TysGpio_Obj p27;
		TysGpio_Obj p28;
		TysGpio_Obj p29;
		TysGpio_Obj p30;
		TysGpio_Obj p31;
    
  }u_pins;
  
  struct TysPinsPrivate {
    
    TysHalGpioPrivate p4;
    TysHalGpioPrivate p5;
		TysHalGpioPrivate p6;
		TysHalGpioPrivate p7;
		TysHalGpioPrivate p8;
		TysHalGpioPrivate p9;
		TysHalGpioPrivate p10;
		TysHalGpioPrivate p11;
		TysHalGpioPrivate p12;
		TysHalGpioPrivate p13;
		TysHalGpioPrivate p14;
		TysHalGpioPrivate p15;
		TysHalGpioPrivate p16;
		TysHalGpioPrivate p17;
		TysHalGpioPrivate p18;
		TysHalGpioPrivate p19;
		TysHalGpioPrivate p20;
		TysHalGpioPrivate p21;
		TysHalGpioPrivate p22;
		TysHalGpioPrivate p23;
		TysHalGpioPrivate p24;
		TysHalGpioPrivate p25;
		TysHalGpioPrivate p26;
		TysHalGpioPrivate p27;
		TysHalGpioPrivate p28;
		TysHalGpioPrivate p29;
		TysHalGpioPrivate p30;
		TysHalGpioPrivate p31;
    
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
  
}TysCdrvMax7301_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvMax7301_Init(TysCdrvMax7301_Obj * const me);
uint8_t CdrvMax7301_SyncUpdate(TysCdrvMax7301_Obj * const me);

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

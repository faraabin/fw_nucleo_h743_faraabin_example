/**
******************************************************************************
* @file           : cdrv_pca9551.h
* @brief          : Header file for cdrv_pca9551.c
* @details        :
* @author         : author's name
* @version        : 0.0.0.1
* @date           : 04/13/2022
* @copyright      : COPYRIGHT(c) 2022 NTP
******************************************************************************
* @attention
*
*
*
******************************************************************************
* @verbatim
* @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_pca9551_H
#define __cdrv_pca9551_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "hal\phal\intf\me_hal_i2c_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

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
    INHERITE_(TysObj)       /*!< Specifies the ---.
                                This parameter can be a value of @ref ---
                                @note . */

    TysI2c_Obj *u_i2c;      /*!< Specifies the ---.
                                This parameter can be a value of @ref ---
                                @note . */

    struct TysPins {
    
    TysGpio_Obj led0;
    TysGpio_Obj led1;
    TysGpio_Obj led2;
    TysGpio_Obj led3;
    TysGpio_Obj led4;
    TysGpio_Obj led5;
    TysGpio_Obj led6;
    TysGpio_Obj led7;
    
  }u_pins;

  struct TysPinsPrivate {
    
    TysHalGpioPrivate led0;
    TysHalGpioPrivate led1;
    TysHalGpioPrivate led2;
    TysHalGpioPrivate led3;
    TysHalGpioPrivate led4;
    TysHalGpioPrivate led5;
    TysHalGpioPrivate led6;
    TysHalGpioPrivate led7;
    
  }privates;

    uint8_t write_value;    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
    uint8_t read_value;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

    uint8_t slave_addr;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

}TysCdrvPCA9551_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvPCA9551_Init(TysCdrvPCA9551_Obj * const me, uint8_t phy_address);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_PCA9551_H */

/************************ (C) COPYRIGHT 2022 NTP *****END OF FILE****/

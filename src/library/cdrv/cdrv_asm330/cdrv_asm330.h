/**
******************************************************************************
* @file           : cdrv_asm330.h
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2023 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2023 FaraabinCo.
* All rights reserved.</center></h2>
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
* @verbatim
* @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_asm330_H
#define __cdrv_asm330_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "hal\phal\intf\me_hal_spi_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "asm330lhh\asm330lhh_reg.h"
#include "library\chrono\me_chrono.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
  bool _init;                 /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysSpi_Obj *Spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysGpio_Obj *Cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysGpio_Obj *Int1;          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysGpio_Obj *Int2;          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint32_t SpiTimeout;        /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  stmdev_ctx_t _sensorCtx;    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  void(*fpInt1Event)(TyeEdge_Event ev);/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  void(*fpInt2Event)(TyeEdge_Event ev);/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _whoAmI;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _reset;             /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysChrono_Obj _timer;       /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  asm330lhh_odr_xl_t AccelOutputDataRate;/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  asm330lhh_odr_g_t GyroOutputDataRate;/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  asm330lhh_fs_xl_t AccelFullScale;/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  asm330lhh_fs_g_t GyroFullScale;/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _isDataReady;       /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  struct _accel {
    float X;
    float Y;
    float Z;
  }Acceleration_mg;

  struct _gyro {
    float X;
    float Y;
    float Z;
  }AngularRate_mdps;

  float Temperature_degC;

}sCdrvAsm330Obj;
/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvAsm330_Init(sCdrvAsm330Obj * const me);
uint8_t fCdrvAsm330_UpdateAccel(sCdrvAsm330Obj * const me);
uint8_t fCdrvAsm330_UpdateGyro(sCdrvAsm330Obj * const me);
uint8_t fCdrvAsm330_UpdateTemp(sCdrvAsm330Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_ASM330_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

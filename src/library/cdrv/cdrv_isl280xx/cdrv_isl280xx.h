/**
******************************************************************************
* @file           : cdrv_isl280xx.h
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
#ifndef __cdrv_isl280xx_H
#define __cdrv_isl280xx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_i2c_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief
  */
typedef enum {
  eBUS_RANGE_16V = 0,
  eBUS_RANGE_32V = 1,
  eBUS_RANGE_60V = 2
}TyeCdrvIsl280xx_Brng;

/**
  * @brief
  */
typedef enum {
  eSHUNT_RANGE_40mV   = 0,
  eSHUNT_RANGE_80mV   = 1,
  eSHUNT_RANGE_160mv  = 2,
  eSHUNT_RANGE_320mV  = 3
}TyeCdrvIsl280xx_Pga;

/**
  * @brief
  */
typedef enum {
  eADC_RES_12Bit1Sample     = 0,
  eADC_RES_13bit1Sample     = 1,
  eADC_RES_14Bit1Sample     = 2,
  eADC_RES_15Bit1Sample     = 3,
  eADC_RES_15Bit2Samples    = 9,
  eADC_RES_15Bit4Samples    = 10,
  eADC_RES_15Bit8Samples    = 11,
  eADC_RES_15Bit16Samples   = 12,
  eADC_RES_15Bit32Samples   = 13,
  eADC_RES_15Bit64Samples   = 14,
  eADC_RES_15Bit128Samples  = 15,
}TyeCdrvIsl280xx_AdcRes;

/**
  * @brief
  */
typedef enum {
  eMODE_PowerDown = 0,
  eMODE_SVTrig   = 1,
  eMODE_BVTrig   = 2,
  eMODE_SVBVTrig = 3,
  eMODE_ADCOff   = 4,
  eMODE_SVCont   = 5,
  eMODE_BVCont   = 6,
  eMODE_SVBVCont = 7,
}TyeCdrvIsl280xx_Mode;

/**
  * @brief
  */
typedef enum {
  eCONNECT_GND = 0,
  eCONNECT_VCC = 1,
  eCONNECT_SDA = 2,
  eCONNECT_SCL = 3,
}TyeCdrvIsl208xx_AddressPinConnection;

/**
  * @brief
  */
typedef struct {
  bool init;                                      /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  uint8_t device_address;                         /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

	uint16_t calibration_register;                  /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  uint16_t config_register;                       /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

	float current_lsb;                              /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

	float power_lsb;                                /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TysI2c_Obj *u_i2c;                              /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TysGpio_Obj *u_exti;                            /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  void(*exti_cb)(TyeEdge_Event ev);               /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TyeCdrvIsl280xx_Brng u_bus_voltage_range;       /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TyeCdrvIsl280xx_Pga u_shunt_voltage_range;      /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TyeCdrvIsl280xx_AdcRes u_bus_adc_resolution;    /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TyeCdrvIsl280xx_AdcRes u_shunt_adc_resolution;  /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  TyeCdrvIsl280xx_Mode u_mode;                    /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

	float u_shunt_resistor;                         /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

  bool u_is_broadcast;                            /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

	char *u_name;                                   /*!< Specifies the ---.
                                                  This parameter can be a value of @ref ---
                                                  @note . */

}TysCdrvIsl280xx_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t CdrvIsl280xx_Init(TysCdrvIsl280xx_Obj * const me, TyeCdrvIsl208xx_AddressPinConnection a0, TyeCdrvIsl208xx_AddressPinConnection a1);
uint8_t CdrvIsl280xx_Reset(TysCdrvIsl280xx_Obj * const me);

uint8_t CdrvIsl280xx_UpdateConfigRegister(TysCdrvIsl280xx_Obj * const me);
void CdrvIsl280xx_ReadConfigRegister(TysCdrvIsl280xx_Obj * const me);
uint8_t CdrvIsl280xx_InterruptCallbackConfig(TysCdrvIsl280xx_Obj * const me, void(*exti_cb)(TyeEdge_Event ev));
uint8_t CdrvIsl280xx_SetCalibrationRegister(TysCdrvIsl280xx_Obj * const me);

uint8_t CdrvIsl280xx_InterruptEnable(TysCdrvIsl280xx_Obj * const me);
uint8_t CdrvIsl280xx_InterruptDisable(TysCdrvIsl280xx_Obj * const me);

float CdrvIsl280xx_ReadShuntVoltage(TysCdrvIsl280xx_Obj * const me);
float CdrvIsl280xx_ReadBusVoltage(TysCdrvIsl280xx_Obj * const me);
float CdrvIsl280xx_ReadPower(TysCdrvIsl280xx_Obj * const me);
float CdrvIsl280xx_ReadCurrent(TysCdrvIsl280xx_Obj * const me);

uint8_t CdrvIsl280xx_SetBusVoltageThreshold(TysCdrvIsl280xx_Obj * const me, float lower_thr, float upper_thr);
uint8_t CdrvIsl280xx_SetShuntVoltageThreshold(TysCdrvIsl280xx_Obj * const me, float lower_thr, float upper_thr);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_ISL280XX_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

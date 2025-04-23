/**
******************************************************************************
* @file           : cdrv_sdp3x.h
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
#ifndef __cdrv_sdp3x_H
#define __cdrv_sdp3x_H

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
typedef enum {
  eSDP3X_TEMPCOMP_MASS_FLOW,
  eSDP3X_TEMPCOMP_DIFFERNTIAL_PRESSURE
}eCdrvSdp3xTempComp;

typedef enum {
  eSDP3X_AVERAGING_NONE,
  eSDP3X_AVERAGING_TILL_READ
}eCdrvSdp3xAveraging;

typedef enum {
	eTRIG_MASS_FLOW = 0,
	eTRIG_DIFF_PRESSURE
}eCdrvSdp3xData;

typedef struct {
	bool _init;
	
	TysI2c_Obj *I2c;
  uint8_t I2cAddress;
	TysGpio_Obj *Irqn;
	
	uint32_t DevProductNumber;
	uint64_t DevSerialNumber;
	float DiffPressure;
	float Temperature;
	
}sCdrvSdp3xObj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvSdp3x_Init(sCdrvSdp3xObj * const me, uint8_t i2cAddr);
uint8_t fCdrvSdp3x_ReadProductId(sCdrvSdp3xObj * const me);

uint8_t fCdrvSdp3x_StartContinousMeasurement(sCdrvSdp3xObj * const me, eCdrvSdp3xTempComp tempConfig, eCdrvSdp3xAveraging avgConfig);
uint8_t fCdrvSdp3x_StopContinousMeasurement(sCdrvSdp3xObj * const me);
uint8_t fCdrvSdp3x_TriggerMeasurement(sCdrvSdp3xObj * const me, eCdrvSdp3xData trigMode);
uint8_t fCdrvSdp3x_ReadMeasurementResults(sCdrvSdp3xObj * const me);
uint8_t fCdrvSdp3x_SoftwareReset(sCdrvSdp3xObj * const me);
uint8_t fCdrvSdp3x_EnterSleepMode(sCdrvSdp3xObj * const me);
uint8_t fCdrvSdp3x_ExitSleepMode(sCdrvSdp3xObj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_SDP3X_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

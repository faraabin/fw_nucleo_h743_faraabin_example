/**
******************************************************************************
* @file           : cdrv_icm20948.h
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2024 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2024 FaraabinCo.
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
#ifndef __cdrv_icm20948_H
#define __cdrv_icm20948_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\core\me_type.h"

#include "library\driver\intf\me_hal_i2c_intf.h"
#include "library\driver\intf\me_hal_gpio_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
	
	eGYRO_CFG_250DPS = 0,
	eGYRO_CFG_500DPS,
	eGYRO_CFG_1000DPS,
	eGYRO_CFG_2000DPS
	
}eCdrvIcm2094GyroFsCfg;

typedef enum {
	
	eGYRO_CFG_LPF_NONE = 10,
	eGYRO_CFG_LPF_0 = 0,
	eGYRO_CFG_LPF_1 = 1,
	eGYRO_CFG_LPF_2 = 2,
	eGYRO_CFG_LPF_3 = 3,
	eGYRO_CFG_LPF_4 = 4,
	eGYRO_CFG_LPF_5 = 5,
	eGYRO_CFG_LPF_6 = 6,
	eGYRO_CFG_LPF_7 = 7,
	
}eCdrvIcm2094GyroLpfCfg;

typedef enum {
	
	eACL_CFG_2G = 0,
	eACL_CFG_4G,
	eACL_CFG_8G,
	eACL_CFG_16G
	
}eCdrvIcm2094AcclFsCfg;

typedef enum {
	
	eACL_CFG_LPF_NONE = 10,
	eACL_CFG_LPF_0 = 0,
	eACL_CFG_LPF_1 = 1,
	eACL_CFG_LPF_2 = 2,
	eACL_CFG_LPF_3 = 3,
	eACL_CFG_LPF_4 = 4,
	eACL_CFG_LPF_5 = 5,
	eACL_CFG_LPF_6 = 6,
	eACL_CFG_LPF_7 = 7,
	
}eCdrvIcm2094AcclLpfCfg;

typedef struct {

  bool _init;
	uint8_t _devAddr;

  TysI2c_Obj *I2c;
  TysGpio_Obj *Interrupt;
  TysGpio_Obj *Fsync;

  float GyroX;
  float GyroY;
  float GyroZ;
	
	float AcclX;
  float AcclY;
  float AcclZ;
	
	eCdrvIcm2094GyroFsCfg _gyroFsCfg;
	bool _gyroFchoice;
	eCdrvIcm2094GyroLpfCfg _gyroLpfCfg;
	
	eCdrvIcm2094AcclFsCfg _acclFsCfg;
	bool _acclFchoice;
	eCdrvIcm2094AcclLpfCfg _acclLpfCfg;

}sCdrvIcm20948Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvIcm20948_Init(sCdrvIcm20948Obj * const me, uint8_t ad0State);
uint8_t fCdrvIcm20948_ReadId(sCdrvIcm20948Obj * const me);
uint8_t fCdrvIcm20948_Reset(sCdrvIcm20948Obj * const me);

uint8_t fCdrvIcm20948_SetGyroCfg(sCdrvIcm20948Obj * const me, eCdrvIcm2094GyroFsCfg fsCfg, eCdrvIcm2094GyroLpfCfg lpfCfg, uint8_t smplrtDiv);
uint8_t fCdrvIcm20948_GetGyroData(sCdrvIcm20948Obj * const me);

uint8_t fCdrvIcm20948_SetAcclCfg(sCdrvIcm20948Obj * const me, eCdrvIcm2094AcclFsCfg fsCfg, eCdrvIcm2094AcclLpfCfg lpfCfg, uint16_t smplrtDiv);
uint8_t fCdrvIcm20948_GetAcclData(sCdrvIcm20948Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_MPU9250_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

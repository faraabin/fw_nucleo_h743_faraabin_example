/**
******************************************************************************
* @file           : cdrv_rm3100.h
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
#ifndef __cdrv_rm3100_H
#define __cdrv_rm3100_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
	
	TysGpio_Obj *u_cs;
	
	TysSpi_Obj *u_spi;
	
	uint8_t revid;
	uint16_t cycleCount;
	float gain;
	
	double uT;
	
	int32_t x_Count;
	int32_t y_Count;
	int32_t z_Count;
	
	float x_uT;
	float y_uT;
	float z_uT;
	
}sCdrvRm3100_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvRm3100_Init(sCdrvRm3100_Obj * const me);
uint8_t fCdrvRm3100_Update(sCdrvRm3100_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_SDP3X_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

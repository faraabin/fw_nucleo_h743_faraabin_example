/**
******************************************************************************
* @file           : cdrv_bmp3xx.h
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
#ifndef __cdrv_bmp3xx_H
#define __cdrv_bmp3xx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "bmp3_defs.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
  bool _init;

  TysGpio_Obj *ChipSelect;
  TysSpi_Obj *Spi;
	uint32_t SpiTimeout;
  TysGpio_Obj *Interrupt;

  struct bmp3_dev _bmp3xxDevice;
}sCdrvBmp3xxObj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvBmp3xx_Init(sCdrvBmp3xxObj * const me);
uint8_t fCdrvBmp3xx_InitChip(sCdrvBmp3xxObj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_BMP5XX_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

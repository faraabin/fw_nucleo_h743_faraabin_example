/**
******************************************************************************
* @file           : cdrv_lps22hb.h
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
#ifndef __cdrv_lps22hb_H
#define __cdrv_lps22hb_H

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
typedef struct {

  bool _init;

  TysI2c_Obj *I2c;
  TysGpio_Obj *Interrupt;

  uint8_t _devAddr;
	
	float Pressure;
	float Temperature;

}sCdrvLps22hbObj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvLps22hb_Init(sCdrvLps22hbObj * const me, uint8_t devAddress);
void fCdrvLps22hb_SoftwareReset(sCdrvLps22hbObj * const me);
uint8_t fCdrvLps22hb_EnableContinuousMode(sCdrvLps22hbObj * const me);
uint8_t fCdrvLps22hb_ReadId(sCdrvLps22hbObj * const me);
uint8_t fCdrvLps22hb_ReadData(sCdrvLps22hbObj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_LPS22HB_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

/**
******************************************************************************
* @file           : cdrv_ads79xx.h
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
#ifndef __cdrv_ads79xx_H
#define __cdrv_ads79xx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"
  
#include "hal\phal\intf\me_hal_spi_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
  eADS79_MODE_MANUAL = 1,
  eADS79_MODE_AUTO1,
  eADS79_MODE_AUTO2
}TyeAds79xxMode;

typedef enum {
  eADS79_RANGE1 = 0,
  eADS79_RANGE2 = 1
}TyeAds79xxRange;

typedef enum {
  eADS79_8BIT = 8,
  eADS79_10BIT = 10,
  eADS79_12BIT = 12
}TyeAds79xxBit;

typedef struct {
  INHERITE_(TysObj)            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysSpi_Obj *u_spi;           /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TyeAds79xxMode u_mode;       /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TyeAds79xxRange u_range;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TyeAds79xxBit u_adc_bits;    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

	uint16_t value_array[16];    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
	
	struct _channels{
		uint16_t ch0;
		uint16_t ch1;
		uint16_t ch2;
		uint16_t ch3;
		uint16_t ch4;
		uint16_t ch5;
		uint16_t ch6;
		uint16_t ch7;
		uint16_t ch8;
		uint16_t ch9;
		uint16_t ch10;
		uint16_t ch11;
		uint16_t ch12;
		uint16_t ch13;
		uint16_t ch14;
		uint16_t ch15;
	}u_raw_value;								 /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
	
  uint8_t manual_channel_counter;/*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint16_t read_value;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

}TysCdrvAds79xx_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t CdrvAds79xx_Init(TysCdrvAds79xx_Obj * const me);
void CdrvAds79xx_Update(TysCdrvAds79xx_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_ADS79XX_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

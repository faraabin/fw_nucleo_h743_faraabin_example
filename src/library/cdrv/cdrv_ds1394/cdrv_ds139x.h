/**
******************************************************************************
* @file           : cdrv_ds139x.h
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
#ifndef __cdrv_ds139x_H
#define __cdrv_ds139x_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_obj.h"
#include "library\type\me_type.h"
#include "library\dsp\me_edge.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"
#include "hal\phal\intf\me_hal_rtc_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 * @brief 
 * 
 */
typedef struct {

  INHERITE_(TysObj)             /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysSpi_Obj *Spi;              /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysGpio_Obj *Cs;              /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint32_t SpiTimeout_ms;       /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysRtc_Obj Rtc;               /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint32_t StartDate;           /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysEdge_Obj _centuryEvent;  /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
}sCdrvDs139x_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvDs139x_Init(sCdrvDs139x_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_DS139X_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

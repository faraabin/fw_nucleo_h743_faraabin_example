/**
******************************************************************************
* @file           : cdrv_cy15b102.h
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
#ifndef __cdrv_cy15b102_H
#define __cdrv_cy15b102_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "library\memory\me_memory_intf.h"
#include "library\chrono\me_chrono.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief
  */
typedef struct {

  bool _init;                 /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysGpio_Obj *Wp;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysGpio_Obj *Cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysSpi_Obj *Spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint32_t SpiTimeout;        /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

}sCdrvCy15b102Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvCy15b102_Init(sCdrvCy15b102Obj * const me);
TysMemory_Obj* fCdrvCy15b102_CreatePartirion(sCdrvCy15b102Obj * const me, uint32_t start_addr, uint32_t size);
uint8_t fCdrvCy15b102_WpDisable(sCdrvCy15b102Obj * const me);
uint8_t fCdrvCy15b102_WpEnable(sCdrvCy15b102Obj * const me);
uint32_t fCdrvCy15b102_GetSize(sCdrvCy15b102Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_CY15B102_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

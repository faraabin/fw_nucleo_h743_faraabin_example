/**
******************************************************************************
* @file           : cdrv_mr25h40.h
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
#ifndef __cdrv_mr25h40_H
#define __cdrv_mr25h40_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\core\me_type.h"
#include "library\core\me_obj.h"
  
#include "library\memory\intf\me_memory_intf.h"
#include "library\utility\chrono\me_chrono.h"

#include "library\driver\intf\me_hal_gpio_intf.h"
#include "library\driver\intf\me_hal_spi_intf.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief
  */
typedef struct {
  bool init;                    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  bool u_enable;                /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysChrono_Obj timer;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t *tmp_buffer;          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_wp;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysSpi_Obj *u_spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

}sCdrvMR25H40_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvMR25H40_Init(sCdrvMR25H40_Obj * const me);
TysMemory_Obj* fCdrvMR25H40_CreatePartirion(sCdrvMR25H40_Obj * const me, uint32_t start_addr, uint32_t size);
uint8_t fCdrvMR25H40_WP_Disable(sCdrvMR25H40_Obj * const me);
uint8_t fCdrvMR25H40_WP_Enable(sCdrvMR25H40_Obj * const me);
uint32_t fCdrvMR25H40_GetSize (sCdrvMR25H40_Obj * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_MR25H40_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

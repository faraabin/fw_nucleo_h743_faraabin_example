/**
 ******************************************************************************
 *  @file 			cdrv_hcms297x.h
 *  @brief 			
 *  @details 		
 *  @author 		Adel Ghaderan
 *  @version 		1.3.0
 *  @date 			1394/12/08
 *  @pre 				
 *  @bug 				
 *  @warning 		
 *  @copyright 	GNU Public License.
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_hcms297x_H
#define __cdrv_hcms297x_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "library\chrono\me_chrono.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
typedef struct {
  
  INHERITE_(TysObj)              /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_bl;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  TysGpio_Obj *u_rst;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  TysGpio_Obj *u_rs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  TysGpio_Obj *u_osc_select;    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysSpi_Obj *u_spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  uint8_t tmp_buffer[100];      /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrvHcms297x_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t	CdrvHcms297x_Init(TysCdrvHcms297x_Obj * const me);
uint8_t	CdrvHcms297x_BlankEnable(TysCdrvHcms297x_Obj * const me);
uint8_t	CdrvHcms297x_BlankDisable(TysCdrvHcms297x_Obj * const me);
uint8_t	CdrvHcms297x_SetContrast(TysCdrvHcms297x_Obj * const me, uint8_t contrast);
uint8_t	CdrvHcms297x_Clear(TysCdrvHcms297x_Obj * const me);
uint8_t	CdrvHcms297x_Print(TysCdrvHcms297x_Obj * const me, uint8_t *data, uint8_t size, uint8_t offset);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__cdrv_hcms297x_H */

/********************************* END OF FILE ********************************/

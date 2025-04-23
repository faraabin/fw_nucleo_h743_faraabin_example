/**
 ******************************************************************************
 *  @file 			cdrv_ads8688.h
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
#ifndef __cdrv_ads8688_H
#define __cdrv_ads8688_H

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
  
  uint8_t addr_byte_qty;        /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_rst;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  TysSpi_Obj *u_spi;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  uint8_t tmp_buffer[100];      /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrvAds8688_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t	CdrvAds8688_Init(TysCdrvAds8688_Obj * const me);
uint8_t	CdrvAds8688_Read(TysCdrvAds8688_Obj * const me, uint16_t *data);

uint8_t	CdrvAds8688_ReadTruckTciAio(TysCdrvAds8688_Obj * const me, uint16_t *data);
uint8_t	CdrvAds8688_ReadTruckPscAio(TysCdrvAds8688_Obj * const me, uint16_t *data);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__cdrv_hcms297x_H */

/********************************* END OF FILE ********************************/

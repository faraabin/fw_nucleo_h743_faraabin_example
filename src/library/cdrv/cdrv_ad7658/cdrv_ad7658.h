/**
 ******************************************************************************
 *  @file 			cdrv_ad7658.h
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
#ifndef __cdrv_ad7658_H
#define __cdrv_ad7658_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "library\chrono\me_chrono.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
typedef enum {
  
  eAD7658_REF_INTERNAL,
  eAD7658_REF_EXTERNAL
  
}TyeAd7658_Reference;

typedef enum {
  
  eAD7658_RANGE_2VREF,
  eAD7658_RANGE_4VREF
  
}TyeAd7658_Range;

typedef struct {
  
  INHERITE_(TysObj)              /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_wr;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_rd;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_cs;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_busy;          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_reset;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_range;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TysGpio_Obj *u_convst;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint16_t(*u_read_port)(void); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  int16_t raw_data[6];          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  float data[6];               /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
}TysCdrvAd7658_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t	CdrvAd7658_Init(TysCdrvAd7658_Obj * const me);
uint8_t	CdrvAd7658_Update(TysCdrvAd7658_Obj * const me);

uint8_t	CdrvAd7658_Reset(TysCdrvAd7658_Obj * const me);

uint8_t	CdrvAd7658_Config_Reference(TysCdrvAd7658_Obj * const me, TyeAd7658_Reference ref);
uint8_t	CdrvAd7658_Config_Range(TysCdrvAd7658_Obj * const me, TyeAd7658_Range range);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__cdrv_hcms297x_H */

/********************************* END OF FILE ********************************/

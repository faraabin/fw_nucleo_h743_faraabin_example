/**
 ******************************************************************************
 *  @file 			cdrvHCMS297x_SMPCmd.h
 *  @brief 			
 *  @details 		
 *  @author 		Adel Ghaderan
 *  @version 		1.0.0
 *  @date 			1394/12/01
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
#ifndef __cdrvHCMS297x_SMPCmd_H
#define __cdrvHCMS297x_SMPCmd_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "modSMP.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
typedef struct
{
	void(*pfInit)(void);
}tyCdrv_HCMS297x_SMPCmd_API_Object_struct;

/* Exported macro ------------------------------------------------------------*/
#define __Cdrv_Create_HCMS297x_SMPCmd_API_Object(__Name) tyCdrv_HCMS297x_SMPCmd_API_Object_struct __Name
#define __Cdrv_Use_HCMS297x_SMPCmd_API_Object(__Name) extern __Cdrv_Create_HCMS297x_SMPCmd_API_Object(__Name)
	
__Cdrv_Use_HCMS297x_SMPCmd_API_Object(aCdrv_HCMS297x_SMPCmd);

/* Exported functions --------------------------------------------------------*/ 
/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__cdrvHCMS297x_SMPCmd_H */

/********************************* END OF FILE ********************************/

/**
 ******************************************************************************
 *  @file 			cdrv_max1161x.h
 *  @brief 			
 *  @details 		
 *  @author 		Adel Ghaderan
 *  @version 		1.3.0
 *  @date 			1396/01/05
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
#ifndef __cdrv_max1161x_H
#define __cdrv_max1161x_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "hal\phal\intf\me_hal_i2c_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
#define MAX11615_REF_VDD      0x00
#define MAX11615_REF_EXTERNAL 0x02
#define MAX11615_REF_INTERNAL 0x04
#define MAX11615_ANANLOG_IN   0x00
#define MAX11615_REF_OUT      0x02
#define MAX11615_INT_REF_ON   0x01

#define ADDRESS_MAX11615  0x66

/* Exported types (enum, struct, union,...)-----------------------------------*/
//typedef enum {
//	eCDRV_AD53x6_CHA 	= 0,
//	eCDRV_AD53x6_CHB,
//	eCDRV_AD53x6_CHC,
//	eCDRV_AD53x6_CHD
//}TyeCdrvAd53x6_ChannelId;

typedef struct {
	uint8_t u_dev_addr;
  uint8_t vref;
	
  TysI2c_Obj *u_i2c;
  uint32_t u_i2c_timeout;
	
  float u_vref;
}TysCdrvMax1161x_Obj;
					
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t CdrvMax1161x_Init(TysCdrvMax1161x_Obj * const me);
uint8_t CdrvMax1161x_Setup(TysCdrvMax1161x_Obj * const me, uint8_t data);
uint8_t CdrvMax1161x_Configuration(TysCdrvMax1161x_Obj * const me, uint8_t data);
uint8_t CdrvMax1161x_ReadRow(TysCdrvMax1161x_Obj * const me, uint8_t ch, uint16_t *val);
uint8_t CdrvMax1161x_Read(TysCdrvMax1161x_Obj * const me, uint8_t ch, float *val);
uint8_t CdrvMax1161x_ScanRow(TysCdrvMax1161x_Obj * const me, uint16_t *data);
uint8_t CdrvMax1161x_Scan(TysCdrvMax1161x_Obj * const me, float *data);
uint8_t CdrvMax1161x_Stretch(TysCdrvMax1161x_Obj * const me);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/********************************* END OF FILE ********************************/

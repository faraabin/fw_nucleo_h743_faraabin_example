/**
 ******************************************************************************
 *  @file 			cdrv_ad53x6.h
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
#ifndef __cdrv_ad53x6_H
#define __cdrv_ad53x6_H

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
#define	CDRV_AD53x6_8BIT 		(uint16_t)0x00FF
#define	CDRV_AD53x6_10BIT 		(uint16_t)0x03FF
#define	CDRV_AD53x6_12BIT 		(uint16_t)0x0FFF

#define	CDRV_AD53x6_GAIN_X1 	(uint16_t)0x0000
#define CDRV_AD53x6_GAIN_X2	(uint16_t)0x8000

#define	CDRV_AD53x6_UNBUF 		(uint16_t)0x0000
#define	CDRV_AD53x6_BUF 			(uint16_t)0x4000
	
/* Exported types (enum, struct, union,...)-----------------------------------*/
typedef enum {
	eCDRV_AD53x6_CHA 	= 0,
	eCDRV_AD53x6_CHB,
	eCDRV_AD53x6_CHC,
	eCDRV_AD53x6_CHD
}TyeCdrvAd53x6_ChannelId;

typedef struct {
	uint8_t u_dev_addr;
	uint16_t u_resolution;
	
	float ch_vref[4];
	uint16_t ch_buf[4];
	uint16_t ch_gain[4];
	
	uint16_t ch_value[4];
	
  TysI2c_Obj *u_i2c;
  uint32_t u_i2c_timeout;
  
}TysCdrvAd53x6_Obj;
					
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t CdrvAd53x6_Init(TysCdrvAd53x6_Obj * const me, uint16_t resolution, uint16_t addr_pin);
uint8_t CdrvAd53x6_ConfigChannel(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, float ref, uint16_t gain, uint16_t buff);

uint8_t CdrvAd53x6_Write(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, float value);
uint8_t CdrvAd53x6_WriteRow(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, uint16_t value);
uint8_t CdrvAd53x6_Read(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, float *value);
uint8_t CdrvAd53x6_ReadAll(TysCdrvAd53x6_Obj * const me, float *value);
uint8_t CdrvAd53x6_ReadRow(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, uint16_t *value);
uint8_t CdrvAd53x6_ReadRowAll(TysCdrvAd53x6_Obj * const me, uint16_t *value);

uint8_t CdrvAd53x6_ClearAll(TysCdrvAd53x6_Obj * const me);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/********************************* END OF FILE ********************************/

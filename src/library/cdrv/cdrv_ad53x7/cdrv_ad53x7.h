/**
 ******************************************************************************
 *  @file 			cdrv_ad53x7.h
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
#ifndef __cdrv_ad53x7_H
#define __cdrv_ad53x7_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "hal\phal\intf\me_hal_spi_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
#define	CDRV_AD53x7_8BIT 		  (uint16_t)0x00FF
#define	CDRV_AD53x7_10BIT 		(uint16_t)0x03FF
#define	CDRV_AD53x7_12BIT 		(uint16_t)0x0FFF

//#define	CDRV_AD53x7_GAIN_X1 	(uint16_t)0x0000
//#define CDRV_AD53x7_GAIN_X2	  (uint16_t)0x2000
#define	CDRV_AD53x7_GAIN_X1 	0
#define CDRV_AD53x7_GAIN_X2	  1

//#define	CDRV_AD53x7_UNBUF 		(uint16_t)0x0000
//#define	CDRV_AD53x7_BUF 			(uint16_t)0x1000
#define	CDRV_AD53x7_UNBUF 		0
#define	CDRV_AD53x7_BUF 			1
	
/* Exported types (enum, struct, union,...)-----------------------------------*/
typedef enum {
	eCDRV_AD53x7_CHA 	= 0,
	eCDRV_AD53x7_CHB,
	eCDRV_AD53x7_CHC,
	eCDRV_AD53x7_CHD
}TyeCdrvAd53x7_ChannelId;

typedef struct {
  
	uint16_t u_resolution;
	
	float ch_vref[4];
	uint16_t ch_buf[4];
	uint16_t ch_gain[4];
	
	uint16_t ch_value[4];
	
  TysSpi_Obj *u_spi;
  TysGpio_Obj *u_cs;
  
}TysCdrvAd53x7_Obj;
					
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
uint8_t CdrvAd53x7_Init(TysCdrvAd53x7_Obj * const me, uint16_t resolution);
uint8_t CdrvAd53x7_ConfigChannel(TysCdrvAd53x7_Obj * const me, TyeCdrvAd53x7_ChannelId ch_id, float ref, uint16_t gain, uint16_t buff);

uint8_t CdrvAd53x7_Write(TysCdrvAd53x7_Obj * const me, TyeCdrvAd53x7_ChannelId ch_id, float value);
uint8_t CdrvAd53x7_WriteRow(TysCdrvAd53x7_Obj * const me, TyeCdrvAd53x7_ChannelId ch_id, uint16_t value);
uint8_t CdrvAd53x7_Read(TysCdrvAd53x7_Obj * const me, TyeCdrvAd53x7_ChannelId ch_id, float *value);
uint8_t CdrvAd53x7_ReadAll(TysCdrvAd53x7_Obj * const me, float *value);
uint8_t CdrvAd53x7_ReadRow(TysCdrvAd53x7_Obj * const me, TyeCdrvAd53x7_ChannelId ch_id, uint16_t *value);
uint8_t CdrvAd53x7_ReadRowAll(TysCdrvAd53x7_Obj * const me, uint16_t *value);

uint8_t CdrvAd53x7_ClearAll(TysCdrvAd53x7_Obj * const me);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/********************************* END OF FILE ********************************/

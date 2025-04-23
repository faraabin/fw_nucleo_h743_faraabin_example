/**
 ******************************************************************************
 *  @file 			cdrv_ad53x6.c
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
 ==============================================================================
                    ##### -------- features #####
 ==============================================================================         
 


									##### How to use -------- #####
 ==============================================================================  
 


 ******************************************************************************
 @verbatim
 @endverbatim
*/
 
/* Includes ------------------------------------------------------------------*/
#include "cdrv_ad53x6.h"
#include "stdlib.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t channel_position[4] = {1,2,4,8};

/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
===============================================================================
                       ##### ---------- functions #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_Init(TysCdrvAd53x6_Obj * const me, uint16_t resolution, uint16_t addr_pin) {
  
  uint8_t tmp[3];
	me->u_resolution = resolution;
	me->u_dev_addr = 0x18 + (addr_pin * 2);
	
	if(me->u_i2c == NULL) {
		return 1;
	}
  
  tmp[0] = 0x01;
  if(meI2c_Transmit_(me->u_i2c, me->u_dev_addr, tmp, 1, me->u_i2c_timeout) != 0) {
		return 1;
	}
	
  if(meI2c_Receive_(me->u_i2c, me->u_dev_addr, tmp, 2, me->u_i2c_timeout) != 0) {
		return 1;
	}
	
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_ConfigChannel(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, float ref, uint16_t gain, uint16_t buff) {
  
  if((uint8_t)ch_id >= 4) {
		return 1;
	}
	
	me->ch_vref[(uint8_t)ch_id] = ref;
	me->ch_gain[(uint8_t)ch_id] = gain;
	me->ch_buf[(uint8_t)ch_id] = buff;
  
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_Write(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, float value) {
  
  if((uint8_t)ch_id >= 4) {
		return 1;
	}
  
  if(me->ch_vref[(uint8_t)ch_id] == 0) {
    return 1;
  }
    
  me->ch_value[(uint8_t)ch_id] = (value / me->ch_vref[(uint8_t)ch_id]) * me->u_resolution;
	
	return(CdrvAd53x6_WriteRow(me, ch_id, me->ch_value[(uint8_t)ch_id]));
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_WriteRow(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, uint16_t value) {
  
  if((uint8_t)ch_id >= 4) {
		return 1;
	}
  
  uint16_t tmp;
  uint8_t tmp_str[3];
	
  me->ch_value[(uint8_t)ch_id] = value;
	switch(me->u_resolution)
	{
		case CDRV_AD53x6_8BIT : 
		{
			tmp = ((me->ch_value[(uint8_t)ch_id] & 0x00FF) << 4)  | 0x3000 | me->ch_gain[(uint8_t)ch_id] | me->ch_buf[(uint8_t)ch_id];
			break;
		}
		
		case CDRV_AD53x6_10BIT : 
		{
			tmp = ((me->ch_value[(uint8_t)ch_id] & 0x03FF) << 2)  | 0x3000 | me->ch_gain[(uint8_t)ch_id] | me->ch_buf[(uint8_t)ch_id];
			break;
		}
		
		case CDRV_AD53x6_12BIT : 
		{
			tmp = ((me->ch_value[(uint8_t)ch_id] & 0x0FFF) << 0)  | 0x3000 | me->ch_gain[(uint8_t)ch_id] | me->ch_buf[(uint8_t)ch_id];
			break;
		}
    
    default: {
      return 1;
    }
	}
	
	tmp_str[0] = channel_position[(uint8_t)ch_id];
	tmp_str[1] = tmp >> 8;
	tmp_str[2] = tmp;
			
  if(meI2c_Transmit_(me->u_i2c, me->u_dev_addr, tmp_str, 3, me->u_i2c_timeout) != 0) {
		return 1;
	}
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_Read(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, float *value) {
  
  if((uint8_t)ch_id >= 4) {
		return 1;
	}
  
  uint16_t tmp;
	
	if(CdrvAd53x6_ReadRow(me, ch_id, &tmp) != 0) {
		return 1;
	}		
	
	*value = me->ch_value[(uint8_t)ch_id] * me->ch_vref[(uint8_t)ch_id] / (float)me->u_resolution;
	
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_ReadAll(TysCdrvAd53x6_Obj * const me, float *value) {
  
  if(CdrvAd53x6_Read(me, eCDRV_AD53x6_CHA, &value[0]) != 0) {
		return 1;
	}		
	
	if(CdrvAd53x6_Read(me, eCDRV_AD53x6_CHB, &value[1]) != 0) {
		return 1;
	}
  
  if(CdrvAd53x6_Read(me, eCDRV_AD53x6_CHC, &value[2]) != 0) {
		return 1;
	}
  
  if(CdrvAd53x6_Read(me, eCDRV_AD53x6_CHD, &value[3]) != 0) {
		return 1;
	}
	
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_ReadRow(TysCdrvAd53x6_Obj * const me, TyeCdrvAd53x6_ChannelId ch_id, uint16_t *value) {
  
  if((uint8_t)ch_id >= 4) {
		return 1;
	}
  
  uint8_t tmp_str[3];
  
  tmp_str[0] = channel_position[(uint8_t)ch_id];
  if(meI2c_Transmit_(me->u_i2c, me->u_dev_addr, tmp_str, 1, me->u_i2c_timeout) != 0) {
		return 1;
	}
	
  if(meI2c_Receive_(me->u_i2c, me->u_dev_addr, tmp_str, 2, me->u_i2c_timeout) != 0) {
		return 1;
	}
	
	uint16_t tmp = ((uint16_t)tmp_str[0] * 0x0100) + (uint16_t)tmp_str[1];
	
	switch(me->u_resolution) {
		case CDRV_AD53x6_8BIT : {
			me->ch_value[(uint8_t)ch_id] = (tmp & 0x0FFF) >> 4;
			break;
		}
		
		case CDRV_AD53x6_10BIT : {
			me->ch_value[(uint8_t)ch_id] = (tmp & 0x0FFF) >> 2;
			break;
		}
		
		case CDRV_AD53x6_12BIT : {
			me->ch_value[(uint8_t)ch_id] = (tmp & 0x0FFF) >> 0;
			break;
		}
    
    default : {
      return 1;
    }
	}
	
	*value = me->ch_value[(uint8_t)ch_id];
	
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_ReadRowAll(TysCdrvAd53x6_Obj * const me, uint16_t *value) {
  
  if(CdrvAd53x6_ReadRow(me, eCDRV_AD53x6_CHA, &value[0]) != 0) {
		return 1;
	}		
	
	if(CdrvAd53x6_ReadRow(me, eCDRV_AD53x6_CHB, &value[1]) != 0) {
		return 1;
	}
  
  if(CdrvAd53x6_ReadRow(me, eCDRV_AD53x6_CHC, &value[2]) != 0) {
		return 1;
	}
  
  if(CdrvAd53x6_ReadRow(me, eCDRV_AD53x6_CHD, &value[3]) != 0) {
		return 1;
	}
	
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAd53x6_ClearAll(TysCdrvAd53x6_Obj * const me) {
  
  uint8_t tmp_str[3];
  
  tmp_str[0] = eCDRV_AD53x6_CHA | eCDRV_AD53x6_CHB | eCDRV_AD53x6_CHC | eCDRV_AD53x6_CHD;
	
	uint16_t tmp = 0x1000;
	tmp_str[1] = tmp >> 8;
	tmp_str[2] = tmp;
	
  if(meI2c_Transmit_(me->u_i2c, me->u_dev_addr, tmp_str, 3, me->u_i2c_timeout) != 0) {
		return 1;
	}
	
  return 0;
}

/**End of Group_Name
  * @}
  */

/********************************* END OF FILE ********************************/

/**
 ******************************************************************************
 *  @file 			cdrv_max1161x.c
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
#include "cdrv_max1161x.h"
#include "stdlib.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
uint8_t CdrvMax1161x_Init(TysCdrvMax1161x_Obj * const me) {
  
  uint8_t ret = 0;
	// 0 - don't care
	// 1 - reset configuration register to default
	// 2 - unipolar
	// 3 - internal clock
	// 4 - SEL0 (vRef)
	// 5 - SEL1 (vRef)
	// 6 - SEL2 (vRef)
	uint8_t vRef = (me->vref<<4) & 0xf0;
	vRef |= 2; // do not reset the setup register
	ret += CdrvMax1161x_Setup(me, vRef);
  
	// 0 - Single Ended
	// 1 to 4 - Channel Select:  7
	// 5 to 6 - Scan Mode: read channels up to selected channel
	uint8_t config_byte = 0x00;
	config_byte |= 1; // single ended mode
	config_byte |= ((1<<5) & (1<<6)); // SCAN bits: convert only the channel selected by CS bits
	ret += CdrvMax1161x_Configuration(me, config_byte);
  
	return ret;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvMax1161x_Setup(TysCdrvMax1161x_Obj * const me, uint8_t data) {
  
  data = data | 0x80; // make REG bit 7 = 1 (setup byte)
  if(meI2c_Transmit_(me->u_i2c, me->u_dev_addr, &data, 1, me->u_i2c_timeout) != 0) { 
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
uint8_t CdrvMax1161x_Configuration(TysCdrvMax1161x_Obj * const me, uint8_t data) {
  
  data = data & (~0x80); // make REG bit 7 = 0 (configuration byte)
  if(meI2c_Transmit_(me->u_i2c, me->u_dev_addr, &data, 1, me->u_i2c_timeout) != 0) { 
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
uint8_t CdrvMax1161x_ReadRow(TysCdrvMax1161x_Obj * const me, uint8_t ch, uint16_t *val) {
  
  uint8_t result[2] = {0,0};

	uint8_t configurationByte = ( (ch<<1) & 0x0e) | 0x61;
	CdrvMax1161x_Configuration(me, configurationByte);
	// the conversion consists of two bytes per channel
  if(meI2c_Receive_(me->u_i2c, me->u_dev_addr, &result[0], 2, me->u_i2c_timeout) != 0){
		return 1;
	}
  
	uint16_t value = 0;
	// cast to uint16_t is necessary to not loose the values by the left shift
	value =  (((uint16_t)result[0] & 0x000f) << 8); // MSB is returned first
	value += ((uint16_t)result[1] & 0x00ff); // read LSB
	*val = value;
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvMax1161x_Read(TysCdrvMax1161x_Obj * const me, uint8_t ch, float *val) {
  
  uint16_t tmp_val;
  
  if(CdrvMax1161x_ReadRow(me, ch, &tmp_val) != 0) {
    return 1;
  }
  
  //Convert row to value
  
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvMax1161x_ScanRow(TysCdrvMax1161x_Obj * const me, uint16_t *data) {
  
  uint8_t ret = 0;
	uint8_t configurationByte = 0xf0;
	ret += CdrvMax1161x_Configuration(me, configurationByte);
	// 2 bytes per channel. There are 8 channels
	for(uint8_t i = 0;i<8;i++){
		ret += CdrvMax1161x_ReadRow(me, i, data+i);
	}
  
	return ret;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvMax1161x_Scan(TysCdrvMax1161x_Obj * const me, float *data) {
  
  uint16_t tmp_val[8];
  
  if(CdrvMax1161x_ScanRow(me, tmp_val) != 0) {
    return 1;
  }
  
  //Convert row to value
  for(uint8_t i=0; i<8; i++) {
    data[i] = (float)tmp_val[i] * me->u_vref / 4095.0f;
  }
  
	return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvMax1161x_Stretch(TysCdrvMax1161x_Obj * const me) {
  
  meI2c_Stretch_(me->u_i2c);
  
  return 0;
}

/**End of Group_Name
  * @}
  */

/********************************* END OF FILE ********************************/

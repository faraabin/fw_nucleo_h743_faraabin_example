/**
******************************************************************************
* @file           : cdrv_endat.c
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

/* Includes ------------------------------------------------------------------*/
#include "cdrv_endat.h"
#include "library\Core\me_type_tool.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct {
  
  uint32_t start    : 1;
  uint32_t alarm    : 1;
  uint32_t data     : 25;
  uint32_t reserve  : 5;
  
}TysEnDat_Struct_25Bit;

typedef struct {
	
	bool			init;
	
	uint32_t	u_poly;
	uint8_t		u_poly_len;
	uint32_t	u_init_val;
	
	uint32_t	appended_data;
	uint8_t		appended_data_len;
	uint32_t	shifted_poly;
	
	uint32_t	u_calculated_crc;
	
} sCrc_Obj;

/* Private variables ---------------------------------------------------------*/
static sCrc_Obj crc_5_itu;

/* Private function prototypes -----------------------------------------------*/
uint8_t Crc_Init(sCrc_Obj *crc_obj);
uint32_t Crc_Calculate(sCrc_Obj *crc_obj, uint32_t input_data, uint8_t data_len);

/* Variables -----------------------------------------------------------------*/

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvEnDat_Init(TysCdrvEnDat_Obj * const me) {
  
  me->init = false;
  
  if( (me->u_data_dir_input == NULL) |
      (me->u_data_dir_output == NULL) | 
      (me->u_spi == NULL)) {
    return 1;
  }
      
  if((me->u_version != eENDAT_VERSION_2p1) && (me->u_version != eENDAT_VERSION_2p2)) {
    return 1;
  }
  
  switch(me->u_resolution) {
    
    case 25: {
      me->coef = 360.0f / (float)(33554432);
      break;
    }
    
    default: {
      return 1;
    }
  }
  if(me->u_resolution != 25) {
    return 1;
  }
  
  me->u_spi->u_role = eSPI_ROLE_MASTER;
  me->u_spi->u_mode  = eSPI_MODE_2;
  me->u_spi->u_data_size = 8;
  me->u_spi->u_bit_order = eSPI_FIRSTBIT_LSB;
  if(meSpi_Init_(me->u_spi) != 0) {
    return 1;
  }
  
  me->u_data_dir_output();
  
  if(me->u_mac_cycle_timeout == 0) {
    me->u_mac_cycle_timeout = 10;
  }
	
	crc_5_itu.u_poly = 0x35;
	crc_5_itu.u_poly_len = 6;
	crc_5_itu.u_init_val = 0x18;
	if(Crc_Init(&crc_5_itu) != 0) {
    return 1;
  }
  
  me->init = true;
  return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvEnDat_Update(TysCdrvEnDat_Obj * const me) {
  
  Tyu_8Byte rx_data;
  uint16_t tx_data;
  uint16_t timeout_cnt = 0;
  
  if(me->init == false) {
    return 1;
  }
  
  me->u_data_dir_output();
  
  meSpi_SetDataSize_(me->u_spi, 10);
  
  tx_data = 0x0007 << 5;
  meSpi_Transmit_(me->u_spi, (uint8_t*)&tx_data, 1, 1000);
  
  me->u_data_dir_input();
  
  meSpi_SetDataSize_(me->u_spi, 8);
  
  while(1) {
    rx_data.byte[0] = 0;
    meSpi_Receive_(me->u_spi, &rx_data.byte[0], 1, 1000);
    
    if(rx_data.byte[0] != 0) {
      meSpi_Receive_(me->u_spi, &rx_data.byte[1], 4, 1000);
      break;
    }
    
    timeout_cnt++;
    if(timeout_cnt > me->u_mac_cycle_timeout) {
      return 1;
    }
  }
  
  Tyu_1Byte tmp8;
  tmp8.u8 = rx_data.byte[0];
  uint8_t index = 0;
  if(tmp8.bit_field8.b0 == 1) {
    index = 0;
  } else if(tmp8.bit_field8.b1 == 1) {
    index = 1;
  } else if(tmp8.bit_field8.b2 == 1) {
    index = 2;
  } else if(tmp8.bit_field8.b3 == 1) {
    index = 3;
  } else if(tmp8.bit_field8.b4 == 1) {
    index = 4;
  } else if(tmp8.bit_field8.b5 == 1) {
    index = 5;
  } else if(tmp8.bit_field8.b6 == 1) {
    index = 6;
  } else if(tmp8.bit_field8.b7 == 1) {
    index = 7;
  }
  
  rx_data.u64 = rx_data.u64 >> index;
  
  TysEnDat_Struct_25Bit *tmps = (TysEnDat_Struct_25Bit*)&rx_data.u64;
  
  me->u_value_raw = tmps->data;
  me->u_value_degree = (float)me->u_value_raw * me->coef;
	me->u_alarm = tmps->alarm;
	me->u_crc = tmps->reserve;
	
	Crc_Calculate(&crc_5_itu, me->u_value_raw, 25);
	if(crc_5_itu.u_calculated_crc == me->u_crc) {
		me->u_data_valid = true;
	} else {
		me->u_data_valid = false;
	}
  
  me->u_data_dir_output();
  
  return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/

/**
 * @brief 
 * 
 * @param crc_obj 
 * @return uint8_t 
 */
uint8_t Crc_Init(sCrc_Obj *crc_obj) {
	
	crc_obj->init = false;
	
	crc_obj->u_calculated_crc = 0;
	
	crc_obj->init = true;
	
	return 0;
}

/**
 * @brief 
 * 
 * @param crc_obj 
 * @param input_data 
 * @param data_len 
 * @return uint32_t 
 */
uint32_t Crc_Calculate(sCrc_Obj *crc_obj, uint32_t input_data, uint8_t data_len) {
	
	if(crc_obj->init == false) {
		return 0;
	}
	
	crc_obj->appended_data_len = data_len + (crc_obj->u_poly_len - 1);
	crc_obj->appended_data = (input_data << (crc_obj->u_poly_len - 1)) + crc_obj->u_init_val;
	crc_obj->shifted_poly = crc_obj->u_poly << (crc_obj->appended_data_len - crc_obj->u_poly_len);
	
	for(int i = 0; i < data_len; i++) {
		
		uint32_t bit_is_one = (crc_obj->appended_data & ((uint32_t)1 << (crc_obj->appended_data_len - i - 1)));
		if(bit_is_one != 0) {
			crc_obj->appended_data ^= crc_obj->shifted_poly;
		} else {
			crc_obj->shifted_poly = crc_obj->shifted_poly >> 1;
			continue;
		}
		
		if(i < (crc_obj->appended_data_len - crc_obj->u_poly_len)) {
			crc_obj->shifted_poly = crc_obj->shifted_poly >> 1;
		} else {
			break;
		}
		
	}
	
	crc_obj->u_calculated_crc = crc_obj->appended_data;
	
	return crc_obj->u_calculated_crc;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

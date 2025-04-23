/**
 ******************************************************************************
 *  @file         cdrv_asc36.c
 *  @brief        ...
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 * DESCRIPTION:
 *
 ******************************************************************************
 * HOW TO USE:
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "cdrv_asc36.h"

#include "faraabin.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAsc36_Init(TysCdrvAsc36_Obj * const me) {
  
  me->init = false;
  
  if((me->u_transmit_receive == NULL) |
     (me->u_data_dir_input == NULL)   |
     (me->u_data_dir_output == NULL)) {
       return 1;
     }
  
  if(me->u_write_direction_pin != NULL) {
    switch(me->u_direction) {
      case eASC36_DIRECTION_CW : {
        me->u_write_direction_pin(0);
        break;
      }
      
      case eASC36_DIRECTION_CCW : {
        me->u_write_direction_pin(1);
        break;
      }
      
      default : {
        return 1;
      }
    }
  }
  
  switch(me->u_protocol) {
    case eASC36_PROTOCOL_SSI_BINARY : {
      break;
    }
  
    default : {
      return 1;
    }
  }
  
  switch(me->u_resolution) {
    case eASC36_RESOLUTION_16BITS:
    case eASC36_RESOLUTION_17BITS:
    case eASC36_RESOLUTION_19BITS:
    case eASC36_RESOLUTION_20BITS: {
      break;
    }
  
    default : {
      return 1;
    }
  }
  
  me->init = true;
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAsc36_Update(TysCdrvAsc36_Obj * const me) {
  
  if(me->init == false) {
    return 1;
  }
  
  me->u_data_dir_output();
  
  if(me->u_transmit_receive(me->tx_buffer, me->rx_buffer, 3) != 0) {
    return 1;
  }
  
  uint32_t tmp = (uint32_t)(((me->rx_buffer[0]) << 16) | (me->rx_buffer[1] << 8) | me->rx_buffer[2]);
  me->u_value_raw = (uint16_t)(tmp >> 7);
  me->u_value_degree = (float)(me->u_value_raw * 360.0f / 65536.0f);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAsc36_SetZero(TysCdrvAsc36_Obj * const me, uint32_t zero_position) {
  
  if(me->init == false) {
    return 1;
  }
  
  if(me->u_write_zero_pin == NULL) {
    return 1;
  }
  
  me->u_write_zero_pin(1);
  meDelay_us_(1000);
  me->u_write_zero_pin(0);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvAsc36_SetDirection(TysCdrvAsc36_Obj * const me, TyeASC36_Direction dir) {
  
  if(me->init == false) {
    return 1;
  }
  
  if(me->u_write_direction_pin == NULL) {
    return 1;
  }
  
  switch(dir) {
    case eASC36_DIRECTION_CW : {
      me->u_direction = dir;
      me->u_write_direction_pin(0);
      break;
    }
    
    case eASC36_DIRECTION_CCW : {
      me->u_direction = dir;
      me->u_write_direction_pin(1);
      break;
    }
    
    default : {
      return 1;
    }
  }
  
  return 0;
}

/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

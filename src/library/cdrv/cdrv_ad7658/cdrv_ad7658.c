/**
 ******************************************************************************
 *  @file 			cdrv_ad7658.c
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
#include "cdrv_ad7658.h"
#include "cdrv_ad7658_ocmd.h"
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
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAd7658_Init(TysCdrvAd7658_Obj * const me) {
  
  meUNIT_INIT_START_();
  
  me->init = false;
  
  if((me->u_read_port == NULL) || (me->u_cs == NULL) || (me->u_rd == NULL) || (me->u_busy == NULL) || (me->u_convst == NULL)) {
    return 1;
  }
  
  me->u_cs->u_dir = eGPIO_DIR_OUTPUT;
  me->u_cs->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_cs));
  meGpio_Set_(me->u_cs);
  
  me->u_rd->u_dir = eGPIO_DIR_OUTPUT;
  me->u_rd->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_rd));
  meGpio_Set_(me->u_rd);
  
  me->u_convst->u_dir = eGPIO_DIR_OUTPUT;
  me->u_convst->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_convst));
  meGpio_Set_(me->u_convst);
  
  me->u_busy->u_dir = eGPIO_DIR_INPUT;
  me->u_busy->u_in_type = eGPIO_PULL_DOWN;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_busy));
  meGpio_Set_(me->u_busy);
  
  if(me->u_wr != NULL) {
    
    me->u_wr->u_dir = eGPIO_DIR_OUTPUT;
    me->u_wr->u_out_type = eGPIO_PUSH_PULL;
    meUNIT_INIT_RET_(meGpio_Init_(me->u_wr));
    meGpio_Set_(me->u_wr);
  }
  
  if(me->u_reset != NULL) {
    
    me->u_reset->u_dir = eGPIO_DIR_OUTPUT;
    me->u_reset->u_out_type = eGPIO_PUSH_PULL;
    meUNIT_INIT_RET_(meGpio_Init_(me->u_reset));
    meGpio_Reset_(me->u_reset);
  }
  
  if(me->u_range != NULL) {
    
    me->u_range->u_dir = eGPIO_DIR_OUTPUT;
    me->u_range->u_out_type = eGPIO_PUSH_PULL;
    meUNIT_INIT_RET_(meGpio_Init_(me->u_range));
    meGpio_Set_(me->u_range);
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
uint8_t	CdrvAd7658_Update(TysCdrvAd7658_Obj * const me) {
  
  if(me->init == false) {
    return 1;
  }
  
  meGpio_Set_(me->u_convst);
  meDelay_us_(2);
  
  meGpio_Set_(me->u_cs);
  meGpio_Set_(me->u_rd);
  
  TysChrono_Obj chrono;
  meChrono_StartTimeout_(&chrono, 10);
  
  uint8_t tmp = 1;
  while(tmp == 1) {
    
    meGpio_Read_(me->u_busy, &tmp);
    
    if(meChrono_us_IsTimedOut(&chrono) == true) {
      return 1;
    }
  }
	
  meGpio_Reset_(me->u_cs);
	
  for(uint8_t i=0; i<6; i++) {
		
    meGpio_Reset_(me->u_rd);
    uint16_t tmp_val = (me->u_read_port() & 0x0FFF);
    
    if(tmp_val > 2048) {
      tmp_val = 4095 - tmp_val;
			tmp_val *= -1;
    }	
    me->raw_data[i] = tmp_val;
      
//    if(tmp_val > 2047) {
//      me->raw_data[i] = -1 * (tmp_val & 0x07FF);
//    } else {
//      me->raw_data[i] = tmp_val;
//    }
    meGpio_Set_(me->u_rd);
    
    meDelay_us_(1);
	}
	
  meGpio_Set_(me->u_cs);
  meGpio_Reset_(me->u_convst);
    
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAd7658_Reset(TysCdrvAd7658_Obj * const me) {
  
  if(me->u_reset == NULL) {
    return 1;
  }
  
  meGpio_Set_(me->u_reset);
  meDelay_us_(1000);
  meGpio_Reset_(me->u_reset);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAd7658_Config_Reference(TysCdrvAd7658_Obj * const me, TyeAd7658_Reference ref) {
  
  if(me->u_wr == NULL) {
    return 1;
  }
  
  switch(ref) {
    
    case eAD7658_REF_INTERNAL: {
      meGpio_Set_(me->u_wr);
      break;
    }
    
    case eAD7658_REF_EXTERNAL: {
      meGpio_Reset_(me->u_wr);
      break;
    }
    
    default:{
      return 1;
    }
  }
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAd7658_Config_Range(TysCdrvAd7658_Obj * const me, TyeAd7658_Range range) {
  
  if(me->u_range == NULL) {
    return 1;
  }
  
  switch(range) {
    
    case eAD7658_RANGE_2VREF: {
      meGpio_Set_(me->u_range);
      break;
    }
    
    case eAD7658_RANGE_4VREF: {
      meGpio_Reset_(me->u_range);
      break;
    }
    
    default:{
      return 1;
    }
  }
  
  return 0;
}

/*
===============================================================================
                       ##### ---------- functions #####
===============================================================================*/

/**End of Group_Name
  * @}
  */

/********************************* END OF FILE ********************************/

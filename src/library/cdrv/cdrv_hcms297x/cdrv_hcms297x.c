/**
 ******************************************************************************
 *  @file 			cdrv_hcms297x.c
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
#include "cdrv_hcms297x.h"
#include "cdrv_hcms297x_ocmd.h"
#include "stdlib.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern const uint8_t aiphanumeric_ascii_5x7[96][5];

/* Private function prototypes -----------------------------------------------*/


/* Variables -----------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvHcms297x_Init(TysCdrvHcms297x_Obj * const me) {
  
  meUNIT_INIT_START_();
  
  me->init = false;
  
  if((me->u_spi == NULL) || (me->u_cs == NULL) || (me->u_rst == NULL) || (me->u_rs == NULL)) {
    return 1;
  }
  
  me->u_spi->u_role = eSPI_ROLE_MASTER;
  me->u_spi->u_mode = eSPI_MODE_0;
  me->u_spi->u_data_size = 8;
  meUNIT_INIT_RET_(meSpi_Init_(me->u_spi));
  
  me->u_cs->u_dir = eGPIO_DIR_OUTPUT;
  me->u_cs->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_cs));
  meGpio_Set_(me->u_cs);
  
  me->u_rst->u_dir = eGPIO_DIR_OUTPUT;
  me->u_rst->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_rst));
  meGpio_Set_(me->u_rst);
  
  if(me->u_bl != NULL) {
    me->u_bl->u_dir = eGPIO_DIR_OUTPUT;
    me->u_bl->u_out_type = eGPIO_PUSH_PULL;
    meUNIT_INIT_RET_(meGpio_Init_(me->u_bl));
    meGpio_Reset_(me->u_bl);
  }
  
  if(me->u_osc_select != NULL) {
    me->u_osc_select->u_dir = eGPIO_DIR_OUTPUT;
    me->u_osc_select->u_out_type = eGPIO_PUSH_PULL;
    meUNIT_INIT_RET_(meGpio_Init_(me->u_osc_select));
    meGpio_Set_(me->u_osc_select);
  }
  
  me->u_rs->u_dir = eGPIO_DIR_OUTPUT;
  me->u_rs->u_out_type = eGPIO_PUSH_PULL;
  meUNIT_INIT_RET_(meGpio_Init_(me->u_rs));
  meGpio_Set_(me->u_rs);
  
  meDelay_ms_(10);
  meGpio_Reset_(me->u_rst);
  meDelay_ms_(10);
  meGpio_Set_(me->u_rst);
  
	CdrvHcms297x_SetContrast(me, 0x0F);
  CdrvHcms297x_Clear(me);
	CdrvHcms297x_SetContrast(me, 0x0F);
	
	me->init = true;
	return 0;
  
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvHcms297x_BlankEnable(TysCdrvHcms297x_Obj * const me) {
  
  if(me->u_bl == NULL) {
    return 1;
  }
  
  meGpio_Set_(me->u_bl);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvHcms297x_BlankDisable(TysCdrvHcms297x_Obj * const me) {
  
  if(me->u_bl == NULL) {
    return 1;
  }
  
  meGpio_Reset_(me->u_bl);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvHcms297x_SetContrast(TysCdrvHcms297x_Obj * const me, uint8_t contrast) {
  
  meGpio_Set_(me->u_rs);
  
  me->tmp_buffer[45] = 0x40 | (contrast & 0x0F);
	me->tmp_buffer[46] = me->tmp_buffer[45];
	
  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, &(me->tmp_buffer[45]), 2, 1000);
	meGpio_Set_(me->u_cs);
	
	meGpio_Reset_(me->u_rs);
  
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvHcms297x_Clear(TysCdrvHcms297x_Obj * const me) {
  
  uint16_t i;
	
	for(i=0; i<8; i++) {
		me->tmp_buffer[42+i] = ' ';
	}
	
	return(CdrvHcms297x_Print(me, &(me->tmp_buffer[42]), 8, 0));
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvHcms297x_Print(TysCdrvHcms297x_Obj * const me, uint8_t *data, uint8_t size, uint8_t offset) {
  
  uint16_t i;
	
	offset = offset % 8;
	
	if(size > 8) {
		size = 8;
	}
	
	if((offset + size) > 8) {
		size = 8 - offset;
	}
	
	for(i=0; i<size; i++) {
		if((data[i] < 0x20) | (data[i] > 0x7F)) {
			return 1;
		}
	}
	
  meGpio_Reset_(me->u_rs);
	
	for(i=0; i<size; i++) {
		me->tmp_buffer[((offset + i) * 5)] 			= aiphanumeric_ascii_5x7[data[i] - 0x20][0];
		me->tmp_buffer[((offset + i) * 5) + 1] 	= aiphanumeric_ascii_5x7[data[i] - 0x20][1];
		me->tmp_buffer[((offset + i) * 5) + 2] 	= aiphanumeric_ascii_5x7[data[i] - 0x20][2];
		me->tmp_buffer[((offset + i) * 5) + 3] 	= aiphanumeric_ascii_5x7[data[i] - 0x20][3];
		me->tmp_buffer[((offset + i) * 5) + 4] 	= aiphanumeric_ascii_5x7[data[i] - 0x20][4];
	}
	
  meGpio_Reset_(me->u_cs);
  meSpi_Transmit_(me->u_spi, me->tmp_buffer, 40, 1000);
	meGpio_Set_(me->u_cs);
		
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

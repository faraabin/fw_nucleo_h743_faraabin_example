/**
 ******************************************************************************
 *  @file 			cdrv_ads8688.c
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
#include "cdrv_ads8688.h"
#include "cdrv_ads8688_ocmd.h"
#include "stdlib.h"

#include "faraabin.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CH_0_INPUT_RANGE 0x05
#define CH_1_INPUT_RANGE 0x06
#define CH_2_INPUT_RANGE 0x07
#define CH_3_INPUT_RANGE 0x08
#define CH_4_INPUT_RANGE 0x09
#define CH_5_INPUT_RANGE 0x0A
#define CH_6_INPUT_RANGE 0x0B
#define CH_7_INPUT_RANGE 0x0C

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
uint8_t	CdrvAds8688_Init(TysCdrvAds8688_Obj * const me) {
	
  meUNIT_INIT_START_();
  me->init = false;
  
  if((me->u_spi == NULL) || (me->u_cs == NULL) || (me->u_rst == NULL)) {
    return 1;
  }
  
  me->u_spi->u_role = eSPI_ROLE_MASTER;
  me->u_spi->u_mode = eSPI_MODE_1;
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
  
  meDelay_ms_(1);
  meGpio_Reset_(me->u_rst);
  meDelay_ms_(1);
  meGpio_Set_(me->u_rst);
  
  meDelay_ms_(100);
  
//  uint8_t tmp_data[2];
//  tmp_data[0] = (CH_0_INPUT_RANGE << 1) | 0x01;
//  tmp_data[1] = 0x00;
  
  me->init = true;
	return 0;
  
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAds8688_Read(TysCdrvAds8688_Obj * const me, uint16_t *data) {
  
  if(me->init == false) {
    return 1;
  }
  
  uint8_t tmp_tx_buffer[10];
  uint8_t tmp_rx_buffer[10];
  
  for(int i=0; i<10; i++) {
    tmp_tx_buffer[i] = 0;
    tmp_rx_buffer[i] = 0;
  }
  
  for(int j=0; j<9; j++) {
    
    meGpio_Reset_(me->u_cs);
    
    //Command
    tmp_tx_buffer[0] = ((j == 0) ? 0xA0 : 0x00);
    tmp_tx_buffer[1] = 0x00;
    
    meGpio_Reset_(me->u_cs);
    meSpi_TransmitReceive_(me->u_spi, tmp_tx_buffer, tmp_rx_buffer, 2, 1000);
    
    for(int i=0; i<4; i++) {
      
      tmp_tx_buffer[0] = 0x00;
      tmp_tx_buffer[1] = 0x00;
      
      meSpi_TransmitReceive_(me->u_spi, tmp_tx_buffer, tmp_rx_buffer, 2, 1000);
      
      if(j != 0) {
        Tyu_2Byte tmp;
        tmp.byte[1] = tmp_rx_buffer[0];
        tmp.byte[0] = tmp_rx_buffer[1];
        data[(i * 8) + (j - 1)] = tmp.u16;
      }
    }
    
    meGpio_Set_(me->u_cs);
    meDelay_us_(2);
  }
    
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAds8688_ReadTruckTciAio(TysCdrvAds8688_Obj * const me, uint16_t *data) {
  
  if(me->init == false) {
    return 1;
  }
  
  uint8_t tmp_tx_buffer[10];
  uint8_t tmp_rx_buffer[10];
  
  for(int i=0; i<10; i++) {
    tmp_tx_buffer[i] = 0;
    tmp_rx_buffer[i] = 0;
  }
  
  for(int j=0; j<9; j++) {
    
    meGpio_Reset_(me->u_cs);
    
    //Command
    tmp_tx_buffer[0] = ((j == 0) ? 0xA0 : 0x00);
    tmp_tx_buffer[1] = 0x00;
    
    meGpio_Reset_(me->u_cs);
    meSpi_TransmitReceive_(me->u_spi, tmp_tx_buffer, tmp_rx_buffer, 2, 1000);
    
    for(int i=0; i<2; i++) {
      
      tmp_tx_buffer[0] = 0x00;
      tmp_tx_buffer[1] = 0x00;
      
      meSpi_TransmitReceive_(me->u_spi, tmp_tx_buffer, tmp_rx_buffer, 2, 1000);
      
      if(j != 0) {
        Tyu_2Byte tmp;
        tmp.byte[1] = tmp_rx_buffer[0];
        tmp.byte[0] = tmp_rx_buffer[1];
        data[(i * 8) + (j - 1)] = tmp.u16;
      }
    }
    
    meGpio_Set_(me->u_cs);
    meDelay_us_(2);
  }
    
  return 0;
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
uint8_t	CdrvAds8688_ReadTruckPscAio(TysCdrvAds8688_Obj * const me, uint16_t *data) {
  
  if(me->init == false) {
    return 1;
  }
  
  uint8_t tmp_tx_buffer[10];
  uint8_t tmp_rx_buffer[10];
  
  for(int i=0; i<10; i++) {
    tmp_tx_buffer[i] = 0;
    tmp_rx_buffer[i] = 0;
  }
  
  for(int j=0; j<9; j++) {
    
    meGpio_Reset_(me->u_cs);
    
    //Command
    tmp_tx_buffer[0] = ((j == 0) ? 0xA0 : 0x00);
    tmp_tx_buffer[1] = 0x00;
    
    meGpio_Reset_(me->u_cs);
    meSpi_TransmitReceive_(me->u_spi, tmp_tx_buffer, tmp_rx_buffer, 2, 1000);
    
    for(int i=0; i<2; i++) {
      
      tmp_tx_buffer[0] = 0x00;
      tmp_tx_buffer[1] = 0x00;
      
      meSpi_TransmitReceive_(me->u_spi, tmp_tx_buffer, tmp_rx_buffer, 2, 1000);
      
      if(j != 0) {
        Tyu_2Byte tmp;
        tmp.byte[1] = tmp_rx_buffer[0];
        tmp.byte[0] = tmp_rx_buffer[1];
        data[(i * 8) + (j - 1)] = tmp.u16;
      }
    }
    
    meGpio_Set_(me->u_cs);
    meDelay_us_(2);
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

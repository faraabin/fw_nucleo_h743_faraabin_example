/**
 ******************************************************************************
 *  @file 			cdrv_stim300.c
 *  @brief 			Driver for use of IMU module in trig mode.
 *  @details 		
 *  @author 		Adel Ghaderan
 *  @version
 *  @date
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
#include "cdrv_stim300.h"

#include "mod_crc32.h"
#include "crc.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint32_t Crc32_Calc(uint8_t *rx_buffer, uint16_t length, uint8_t dummy_byte_qty);

/* Variables -----------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*
===============================================================================
                       ##### ---------- functions #####
===============================================================================*/
/**
  * @brief Interpret received packet from IMU.
  * @note  
  * @param  
  * @retval  0 on OK, otherwize error.
*/
uint8_t CdrvStim300_Interpret(TysCdrvStim300_Obj *me, uint8_t *rx_buffer, uint16_t length) {
  
  switch(rx_buffer[0]) {
//  case eRATE : {
////    if((length != eRATE_LENGTH) && (length != (eRATE_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_packet *pkt = (struct rate_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_ACC : {
//    //if((length != eRATE_ACC_LENGTH) && (length != (eRATE_ACC_LENGTH + 2))) {
//    //  return 1;
//    //}
//    
//    struct rate_accl_packet *pkt = (struct rate_accl_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_LENGTH, 0) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    /*rate*/
//    me->data.identifier = rx_buffer[0];
//    
//    me->data.gyro_x = (double)((int)(  (pkt->gyro_x.value[0] << 24)
//                                     + (pkt->gyro_x.value[1] << 16)
//                                     + (pkt->gyro_x.value[2] << 8)) >> 8) / 0x4000; //2^14
//    
//    me->data.gyro_y = (double)((int)(  (pkt->gyro_y.value[0] << 24)
//                                     + (pkt->gyro_y.value[1] << 16)
//                                     + (pkt->gyro_y.value[2] << 8)) >> 8) / 0x4000; //2^14
//    
//    me->data.gyro_z = (double)((int)(  (pkt->gyro_z.value[0] << 24)
//                                     + (pkt->gyro_z.value[1] << 16)
//                                     + (pkt->gyro_z.value[2] << 8)) >> 8) / 0x4000; //2^14
//    
//    me->data.gyros_status.byte = pkt->gyros_status.byte;
//    /*accl*/
//    me->data.acc_x = (double)((int)(  (pkt->acc_x.value[0] << 24)
//                                     + (pkt->acc_x.value[1] << 16)
//                                     + (pkt->acc_x.value[2] << 8)) >> 8) / 0x040000; //2^18
//    
//    me->data.acc_y = (double)((int)(  (pkt->acc_y.value[0] << 24)
//                                     + (pkt->acc_y.value[1] << 16)
//                                     + (pkt->acc_y.value[2] << 8)) >> 8) / 0x040000; //2^18
//    
//    me->data.acc_z = (double)((int)(  (pkt->acc_z.value[0] << 24)
//                                     + (pkt->acc_z.value[1] << 16)
//                                     + (pkt->acc_z.value[2] << 8)) >> 8) / 0x040000; //2^18
//    
//    me->data.acc_status.byte = pkt->acc_status.byte;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_INCLI : {
////    if((length != eRATE_INCLI_LENGTH) && (length != (eRATE_INCLI_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_incl_packet *pkt = (struct rate_incl_packet*)rx_buffer;
//    
////    if(ModCrc32_NewCalc(rx_buffer, eRATE_INCLI_LENGTH) != pkt->checksum) {
////      return 1;
////    }
//    
//    /* Copy Data */
//    me->data.identifier = pkt->identifier;
//    
//    me->data.gyro_x = (double)((int)(  (pkt->gyro_x.value[0] << 24)
//                                     + (pkt->gyro_x.value[1] << 16)
//                                     + (pkt->gyro_x.value[2] << 8)) >> 8) / 0x4000; //2^14
//    
//    me->data.gyro_y = (double)((int)(  (pkt->gyro_y.value[0] << 24)
//                                     + (pkt->gyro_y.value[1] << 16)
//                                     + (pkt->gyro_y.value[2] << 8)) >> 8) / 0x4000; //2^14
//    
//    me->data.gyro_z = (double)((int)(  (pkt->gyro_z.value[0] << 24)
//                                     + (pkt->gyro_z.value[1] << 16)
//                                     + (pkt->gyro_z.value[2] << 8)) >> 8) / 0x4000; //2^14
//    
//    me->data.gyros_status = pkt->gyros_status;
//    
//    me->data.incl_x = (double)((int)(  (pkt->incl_x.value[0] << 24)
//                                     + (pkt->incl_x.value[1] << 16)
//                                     + (pkt->incl_x.value[2] << 8)) >> 8) / 0x400000; //2^22
//    
//    me->data.incl_y = (double)((int)(  (pkt->incl_y.value[0] << 24)
//                                     + (pkt->incl_y.value[1] << 16)
//                                     + (pkt->incl_y.value[2] << 8)) >> 8) / 0x400000; //2^22
//    
//    me->data.incl_z = (double)((int)(  (pkt->incl_z.value[0] << 24)
//                                     + (pkt->incl_z.value[1] << 16)
//                                     + (pkt->incl_z.value[2] << 8)) >> 8) / 0x400000; //2^22
//    
//    me->data.incl_status = pkt->incl_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
  case eRATE_ACC_INCLI : {
    
    if((length != eRATE_ACC_INCLI_LENGTH) && (length != (eRATE_ACC_INCLI_LENGTH + 2))) {
      return 1;
    }
    
    struct rate_acc_incl_packet *pkt = (struct rate_acc_incl_packet*)rx_buffer;
    
    /*if(Crc32_Calc(rx_buffer, eRATE_ACC_INCLI_LENGTH, 2) != pkt->checksum) {
      return 1;
    }*/
    
    /* Copy Data */
    me->data.identifier = pkt->identifier;
    
    me->data.gyros_status.byte = pkt->gyros_status.byte;
    
    if(me->data.gyros_status.byte == 0) {
      
      me->data.gyro_x = (double)((int)(  (pkt->gyro_x.value[0] << 24)
                                       + (pkt->gyro_x.value[1] << 16)
                                       + (pkt->gyro_x.value[2] << 8)) >> 8) / 0x4000; //2^14
      
      me->data.gyro_y = (double)((int)(  (pkt->gyro_y.value[0] << 24)
                                       + (pkt->gyro_y.value[1] << 16)
                                       + (pkt->gyro_y.value[2] << 8)) >> 8) / 0x4000; //2^14
      
      me->data.gyro_z = (double)((int)(  (pkt->gyro_z.value[0] << 24)
                                       + (pkt->gyro_z.value[1] << 16)
                                       + (pkt->gyro_z.value[2] << 8)) >> 8) / 0x4000; //2^14
    }
    
    me->data.incl_status.byte = pkt->acc_status.byte;
    
    if(me->data.incl_status.byte == 0) {
      
      me->data.incl_x = (double)((int)(  (pkt->incl_x.value[0] << 24)
                                       + (pkt->incl_x.value[1] << 16)
                                       + (pkt->incl_x.value[2] << 8)) >> 8) / 0x400000; //2^22
      
      me->data.incl_y = (double)((int)(  (pkt->incl_y.value[0] << 24)
                                       + (pkt->incl_y.value[1] << 16)
                                       + (pkt->incl_y.value[2] << 8)) >> 8) / 0x400000; //2^22
      
      me->data.incl_z = (double)((int)(  (pkt->incl_z.value[0] << 24)
                                       + (pkt->incl_z.value[1] << 16)
                                       + (pkt->incl_z.value[2] << 8)) >> 8) / 0x400000; //2^22
    }
    
    me->data.acc_status.byte = pkt->acc_status.byte;
    
    if(me->data.acc_status.byte == 0) {
      
      me->data.acc_x = (double)((int)(  (pkt->acc_x.value[0] << 24)
                                       + (pkt->acc_x.value[1] << 16)
                                       + (pkt->acc_x.value[2] << 8)) >> 8) / 0x040000; //2^18
      
      me->data.acc_y = (double)((int)(  (pkt->acc_y.value[0] << 24)
                                       + (pkt->acc_y.value[1] << 16)
                                       + (pkt->acc_y.value[2] << 8)) >> 8) / 0x040000; //2^18
      
      me->data.acc_z = (double)((int)(  (pkt->acc_z.value[0] << 24)
                                       + (pkt->acc_z.value[1] << 16)
                                       + (pkt->acc_z.value[2] << 8)) >> 8) / 0x040000; //2^18
    }
    
    
    
    me->data.counter = pkt->counter;
    
    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
//    me->data.acc_status = pkt->acc_status;
//    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
//    me->data.incl_status = pkt->incl_status;
//    
//    me->data.counter = pkt->counter;
    
    break;
  }
  
//  case eRATE_TEMP : {
////    if((length != eRATE_TEMP_LENGTH) && (length != (eRATE_TEMP_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_tmp_packet *pkt = (struct rate_tmp_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_TEMP_LENGTH, 3) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
//    me->data.gyro_temp_status = pkt->gyro_temp_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_ACC_TEMP : {
////    if((length != eRATE_ACC_TEMP_LENGTH) && (length != (eRATE_ACC_TEMP_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_acc_tmp_packet *pkt = (struct rate_acc_tmp_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_TEMP_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
//    me->data.acc_status = pkt->acc_status;
//    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
//    me->data.gyro_temp_status = pkt->gyro_temp_status;
//    
////    me->data.acc_temp_x = pkt->acc_temp_x;
////    me->data.acc_temp_y = pkt->acc_temp_y;
////    me->data.acc_temp_z = pkt->acc_temp_z;
//    me->data.acc_temp_status = pkt->acc_temp_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_INCLI_TEMP : {
////    if((length != eRATE_INCLI_TEMP_LENGTH) && (length != (eRATE_INCLI_TEMP_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_incl_tmp_packet *pkt = (struct rate_incl_tmp_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_INCLI_TEMP_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
//    me->data.incl_status = pkt->incl_status;
//    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
//    me->data.gyro_temp_status = pkt->gyro_temp_status;
//    
////    me->data.incl_temp_x = pkt->incl_temp_x;
////    me->data.incl_temp_y = pkt->incl_temp_y;
////    me->data.incl_temp_z = pkt->incl_temp_z;
//    me->data.incl_temp_status = pkt->incl_temp_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_ACC_INCLI_TEMP : {
////    if((length != eRATE_ACC_INCLI_TEMP_LENGTH) && (length != (eRATE_ACC_INCLI_TEMP_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_acc_incl_tmp_packet *pkt = (struct rate_acc_incl_tmp_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_INCLI_TEMP_LENGTH, 1) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
//    me->data.acc_status = pkt->acc_status;
//    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
//    me->data.incl_status = pkt->incl_status;
//    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
//    me->data.gyro_temp_status = pkt->gyro_temp_status;
//    
////    me->data.acc_temp_x = pkt->acc_temp_x;
////    me->data.acc_temp_y = pkt->acc_temp_y;
////    me->data.acc_temp_z = pkt->acc_temp_z;
//    me->data.acc_temp_status = pkt->acc_temp_status;
//    
////    me->data.incl_temp_x = pkt->incl_temp_x;
////    me->data.incl_temp_y = pkt->incl_temp_y;
////    me->data.incl_temp_z = pkt->incl_temp_z;
//    me->data.incl_temp_status = pkt->incl_temp_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_AUX : {
////    if((length != eRATE_AUX_LENGTH) && (length != (eRATE_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_aux_packet *pkt = (struct rate_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_AUX_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_ACC_AUX : {
////    if((length != eRATE_ACC_AUX_LENGTH) && (length != (eRATE_ACC_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_acc_aux_packet *pkt = (struct rate_acc_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_AUX_LENGTH, 0) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
//    me->data.acc_status = pkt->acc_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_INCLI_AUX : {
////    if((length != eRATE_INCLI_AUX_LENGTH) && (length != (eRATE_INCLI_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_incl_aux_packet *pkt = (struct rate_incl_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_INCLI_AUX_LENGTH, 0) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
//    me->data.incl_status = pkt->incl_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_ACC_INCLI_AUX : {
////    if((length != eRATE_ACC_INCLI_AUX_LENGTH) && (length != (eRATE_ACC_INCLI_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_acc_incl_aux_packet *pkt = (struct rate_acc_incl_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_INCLI_AUX_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
//    me->data.acc_status = pkt->acc_status;
//    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
//    me->data.incl_status = pkt->incl_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
//  case eRATE_TEMP_AUX : {
////    if((length != eRATE_TEMP_AUX_LENGTH) && (length != (eRATE_TEMP_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_tmp_aux_packet *pkt = (struct rate_tmp_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_TEMP_AUX_LENGTH, 3) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
//    me->data.gyro_temp_status = pkt->gyro_temp_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
//  
//  case eRATE_ACC_TEMP_AUX : {
////    if((length != eRATE_ACC_TEMP_AUX_LENGTH) && (length != (eRATE_ACC_TEMP_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_acc_tmp_aux_packet *pkt = (struct rate_acc_tmp_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_TEMP_AUX_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
//    me->data.gyros_status = pkt->gyros_status;
//    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
//    me->data.acc_status = pkt->acc_status;
//    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
//    me->data.gyro_temp_status = pkt->gyro_temp_status;
//    
////    me->data.acc_temp_x = pkt->acc_temp_x;
////    me->data.acc_temp_y = pkt->acc_temp_y;
////    me->data.acc_temp_z = pkt->acc_temp_z;
//    me->data.acc_temp_status = pkt->acc_temp_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
//  
//  case eRATE_INCLI_TEMP_AUX : {
////    if((length != eRATE_INCLI_TEMP_AUX_LENGTH) && (length != (eRATE_INCLI_TEMP_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct rate_incl_tmp_aux_packet *pkt = (struct rate_incl_tmp_aux_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_INCLI_TEMP_AUX_LENGTH, 2) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
////    me->data.gyros_status = pkt->gyros_status;
////    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
////    me->data.incl_status = pkt->incl_status;
////    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
////    me->data.gyro_temp_status = pkt->gyro_temp_status;
////    
////    me->data.incl_temp_x = pkt->incl_temp_x;
////    me->data.incl_temp_y = pkt->incl_temp_y;
////    me->data.incl_temp_z = pkt->incl_temp_z;
////    me->data.incl_temp_status = pkt->incl_temp_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
//  
//  case eRATE_ACC_INCLI_TEMP_AUX : {
////    if((length != eRATE_ACC_INCLI_TEMP_AUX_LENGTH) && (length != (eRATE_ACC_INCLI_TEMP_AUX_LENGTH + 2))) {
////      return 1;
////    }
//    
//    struct full_packet *pkt = (struct full_packet*)rx_buffer;
//    
//    if(Crc32_Calc(rx_buffer, eRATE_ACC_INCLI_TEMP_AUX_LENGTH, 1) != pkt->checksum) {
//      return 1;
//    }
//    
//    /* Copy Data */
//    me->data.identifier = rx_buffer[0];
//    
////    me->data.gyro_x = pkt->gyro_x;
////    me->data.gyro_y = pkt->gyro_y;
////    me->data.gyro_z = pkt->gyro_z;
////    me->data.gyros_status = pkt->gyros_status;
////    
////    me->data.acc_x = pkt->acc_x;
////    me->data.acc_y = pkt->acc_y;
////    me->data.acc_z = pkt->acc_z;
////    me->data.acc_status = pkt->acc_status;
////    
////    me->data.incl_x = pkt->incl_x;
////    me->data.incl_y = pkt->incl_y;
////    me->data.incl_z = pkt->incl_z;
////    me->data.incl_status = pkt->incl_status;
////    
////    me->data.gyro_temp_x = pkt->gyro_temp_x;
////    me->data.gyro_temp_y = pkt->gyro_temp_y;
////    me->data.gyro_temp_z = pkt->gyro_temp_z;
////    me->data.gyro_temp_status = pkt->gyro_temp_status;
////    
////    me->data.acc_temp_x = pkt->acc_temp_x;
////    me->data.acc_temp_y = pkt->acc_temp_y;
////    me->data.acc_temp_z = pkt->acc_temp_z;
////    me->data.acc_temp_status = pkt->acc_temp_status;
////    
////    me->data.incl_temp_x = pkt->incl_temp_x;
////    me->data.incl_temp_y = pkt->incl_temp_y;
////    me->data.incl_temp_z = pkt->incl_temp_z;
////    me->data.incl_temp_status = pkt->incl_temp_status;
//    
//    me->data.aux = pkt->aux;
//    me->data.aux_status = pkt->aux_status;
//    
//    me->data.counter = pkt->counter;
//    
//    break;
//  }
  
  default : {
    //error received frame
    return 1;
  }
  }
  
  return 0;
}

/**
  * @brief This function calculate crc for a block of data.
  * @note  
  * @param  
  * @retval crc value
*/
uint8_t crc_str[200];
uint32_t Crc32_Calc(uint8_t *rx_buffer, uint16_t length, uint8_t dummy_byte_qty) {
  
  uint16_t i=0;
  
  for(i=0; i<200; i++) {
    crc_str[i] = 0x00;
  }
  
  for(i=0; i<(length - 4); i++) {
    crc_str[i] = rx_buffer[i];
  }
  
  for(i=0; i<dummy_byte_qty; i++) {
    crc_str[(length - 4) + i] = 0x00;
  }
  
  //uint32_t crc32 = ModCrc32_InitValue(0xFFFFFFFF);
  //crc32 = ModCrc32_FastCalculate(crc32, str, (length - 4) + dummy_byte_qty);
  uint32_t crc32 = ModCrc32_NewCalc(crc_str, (length - 4) + dummy_byte_qty);
  //uint32_t crc32 = crcSlow(crc_str, (length - 4) + dummy_byte_qty);
  //crcInit();
  //uint32_t crc32 = crcFast(crc_str, (length - 4) + dummy_byte_qty);
  
  return meEndian_Reverse_u32(crc32);
}

/**End of Group_Name
  * @}
  */

/********************************* END OF FILE ********************************/

/**
 ******************************************************************************
 *  @file 			cdrv_stim300.h
 *  @brief 			
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
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_stim300_H
#define __cdrv_stim300_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
enum DATAGRAM_CONTENT{
  eRATE = 0x90,
  eRATE_ACC = 0x91,
  eRATE_INCLI = 0x92,
  eRATE_ACC_INCLI = 0x93,
  eRATE_TEMP = 0x94,
  eRATE_ACC_TEMP = 0xA5,
  eRATE_INCLI_TEMP = 0xA6,
  eRATE_ACC_INCLI_TEMP = 0xA7,
  eRATE_AUX = 0x98,
  eRATE_ACC_AUX = 0x99,
  eRATE_INCLI_AUX = 0x9A,
  eRATE_ACC_INCLI_AUX = 0x9B,
  eRATE_TEMP_AUX = 0x9C,
  eRATE_ACC_TEMP_AUX = 0xAD,
  eRATE_INCLI_TEMP_AUX = 0xAE,
  eRATE_ACC_INCLI_TEMP_AUX = 0xAF
};
  
 enum DATAGRAM_CONTENT_LENGTH{
  eRATE_LENGTH = 18,
  eRATE_ACC_LENGTH = 28,
  eRATE_INCLI_LENGTH = 28,
  eRATE_ACC_INCLI_LENGTH = 38,
  eRATE_TEMP_LENGTH = 25,
  eRATE_ACC_TEMP_LENGTH = 42,
  eRATE_INCLI_TEMP_LENGTH = 42,
  eRATE_ACC_INCLI_TEMP_LENGTH = 59,
  eRATE_AUX_LENGTH = 22,
  eRATE_ACC_AUX_LENGTH = 32,
  eRATE_INCLI_AUX_LENGTH = 32,
  eRATE_ACC_INCLI_AUX_LENGTH = 42,
  eRATE_TEMP_AUX_LENGTH = 29,
  eRATE_ACC_TEMP_AUX_LENGTH = 46,
  eRATE_INCLI_TEMP_AUX_LENGTH = 46,
  eRATE_ACC_INCLI_TEMP_AUX_LENGTH = 63
};

__packed struct  status_bit {
  uint8_t x:1;
  uint8_t y:1;
  uint8_t z:1;
  uint8_t measurement_error:1;
  uint8_t overload:1;
  uint8_t outside_condition:1;
  uint8_t startup:1;
  uint8_t integrity_error:1;
};

__packed union  status_byte {
  struct  status_bit bit;
  uint8_t byte;
};

__packed struct sensor_value {
  uint8_t value[3];
};

__packed struct  temp_value {
  uint8_t value[2];
};

__packed struct full_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  int16_t acc_temp_x;
  int16_t acc_temp_y;
  int16_t acc_temp_z;
  union status_byte acc_temp_status;
  int16_t incl_temp_x;
  int16_t incl_temp_y;
  int16_t incl_temp_z;
  union status_byte incl_temp_status;
  struct sensor_value aux;
  union status_byte aux_status;
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_accl_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;

  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_incl_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_acc_incl_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_tmp_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_acc_tmp_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  int16_t acc_temp_x;
  int16_t acc_temp_y;
  int16_t acc_temp_z;
  union status_byte acc_temp_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_incl_tmp_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  int16_t incl_temp_x;
  int16_t incl_temp_y;
  int16_t incl_temp_z;
  union status_byte incl_temp_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_acc_incl_tmp_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  int16_t acc_temp_x;
  int16_t acc_temp_y;
  int16_t acc_temp_z;
  union status_byte acc_temp_status;
  int16_t incl_temp_x;
  int16_t incl_temp_y;
  int16_t incl_temp_z;
  union status_byte incl_temp_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value aux;
  union status_byte aux_status;
 
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_acc_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  struct sensor_value aux;
  union status_byte aux_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_incl_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  struct sensor_value aux;
  union status_byte aux_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_acc_incl_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  struct sensor_value aux;
  union status_byte aux_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_tmp_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  struct sensor_value aux;
  union status_byte aux_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_acc_tmp_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value acc_x;
  struct sensor_value acc_y;
  struct sensor_value acc_z;
  union status_byte acc_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  int16_t acc_temp_x;
  int16_t acc_temp_y;
  int16_t acc_temp_z;
  union status_byte acc_temp_status;
  struct sensor_value aux;
  union status_byte aux_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct rate_incl_tmp_aux_packet {
  uint8_t identifier;
  struct sensor_value gyro_x;
  struct sensor_value gyro_y;
  struct sensor_value gyro_z;
  union status_byte gyros_status;
  struct sensor_value incl_x;
  struct sensor_value incl_y;
  struct sensor_value incl_z;
  union status_byte incl_status;
  int16_t gyro_temp_x;
  int16_t gyro_temp_y;
  int16_t gyro_temp_z;
  union status_byte gyro_temp_status;
  int16_t incl_temp_x;
  int16_t incl_temp_y;
  int16_t incl_temp_z;
  union status_byte incl_temp_status;
  struct sensor_value aux;
  union status_byte aux_status;
  
  uint8_t counter;
  uint16_t latency;
  uint32_t checksum;
  uint8_t cr;
  uint8_t lf;
};

__packed struct data_packet {
  uint8_t identifier;
  double gyro_x;
  double gyro_y;
  double gyro_z;
  union status_byte gyros_status;
  double acc_x;
  double acc_y;
  double acc_z;
  union status_byte acc_status;
  double incl_x;
  double incl_y;
  double incl_z;
  union status_byte incl_status;
  double gyro_temp_x;
  double gyro_temp_y;
  double gyro_temp_z;
  union status_byte gyro_temp_status;
  double acc_temp_x;
  double acc_temp_y;
  double acc_temp_z;
  union status_byte acc_temp_status;
  double incl_temp_x;
  double incl_temp_y;
  double incl_temp_z;
  union status_byte incl_temp_status;
  struct sensor_value aux;
  union status_byte aux_status;
  uint8_t counter;
  uint16_t latency;
};

typedef struct {
  struct data_packet data;
  void(*trig_write)(uint8_t val);
}TysCdrvStim300_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
//uint8_t CdrvStim300_Init(void);

uint8_t CdrvStim300_Interpret(TysCdrvStim300_Obj *me, uint8_t *rx_buffer, uint16_t length);

/* Extern functions ----------------------------------------------------------*/ 

/**End of Group_Name
  * @}
  */ 

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/********************************* END OF FILE ********************************/

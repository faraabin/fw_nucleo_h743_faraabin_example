/**
 ******************************************************************************
 *  @file         cdrv_asc36.h
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
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_asc36_H
#define __cdrv_asc36_H

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
/**
  * @brief
  */
typedef enum {
  eASC36_RESOLUTION_16BITS,
  eASC36_RESOLUTION_17BITS,
  eASC36_RESOLUTION_19BITS,
  eASC36_RESOLUTION_20BITS
}TyeASC36_Resolution;

/**
  * @brief
  */
typedef enum {
  eASC36_PROTOCOL_SSI_BINARY,
  eASC36_PROTOCOL_SSI_GRAY,
  eASC36_PROTOCOL_BISS_C
}TyeASC36_Protocol;

/**
  * @brief
  */
typedef enum {
  eASC36_DIRECTION_CW,
  eASC36_DIRECTION_CCW
}TyeASC36_Direction;

#pragma push
#pragma pack(1)
/**
  * @brief
  */
typedef struct {
  
  bool init; /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TyeASC36_Resolution u_resolution; /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TyeASC36_Direction u_direction; /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  TyeASC36_Protocol u_protocol; /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t(*u_transmit_receive)(uint8_t *tx_data, uint8_t *rx_data, uint16_t size); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t(*u_write_zero_pin)(uint8_t value); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t(*u_write_direction_pin)(uint8_t value); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
	uint8_t(*u_data_dir_input)(void); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
	
  uint8_t(*u_data_dir_output)(void); /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint32_t u_value_raw;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  float u_value_degree;         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t tx_buffer[50];         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
                               
  uint8_t rx_buffer[50];         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrvAsc36_Obj;
#pragma pop

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvAsc36_Init(TysCdrvAsc36_Obj * const me);
uint8_t CdrvAsc36_Update(TysCdrvAsc36_Obj * const me);
uint8_t CdrvAsc36_SetZero(TysCdrvAsc36_Obj * const me, uint32_t zero_position);
uint8_t CdrvAsc36_SetDirection(TysCdrvAsc36_Obj * const me, TyeASC36_Direction dir);

/* Extern functions ----------------------------------------------------------*/
/* Extern Object or Variable -------------------------------------------------*/

/**End of Group_Name
  * @}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

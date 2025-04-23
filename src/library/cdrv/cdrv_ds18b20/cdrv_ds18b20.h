/**
 ******************************************************************************
 *  @file         cdrv_ds18b20.h
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
#ifndef __cdrv_ds18b20_H
#define __cdrv_ds18b20_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

#include "library\protocol\prtl_one_wire\prtl_one_wire.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/* Every onewire chip has different ROM code, but all the same chips has same family code */
/* in case of DS18B20 this is 0x28 and this is first byte of ROM address */
#define DS18B20_FAMILY_CODE			    0x28
#define DS18B20_CMD_ALARMSEARCH			0xEC

/* DS18B20 read temperature command */
#define DS18B20_CMD_CONVERTTEMP			  0x44 	/* Convert temperature */
#define DS18B20_DECIMAL_STEPS_12BIT		0.0625
#define DS18B20_DECIMAL_STEPS_11BIT		0.125
#define DS18B20_DECIMAL_STEPS_10BIT		0.25
#define DS18B20_DECIMAL_STEPS_9BIT		0.5

/* Bits locations for resolution */
#define DS18B20_RESOLUTION_R1			6
#define DS18B20_RESOLUTION_R0			5

/* CRC enabled */
#ifdef DS18B20_USE_CRC	
#define DS18B20_DATA_LEN			9
#else
#define DS18B20_DATA_LEN			2
#endif

/* Exported types (enum, struct, union,...)-----------------------------------*/
/**
  * @brief
  */
typedef enum {
  eDS18B20_RESOLUTION_9BITS = 9,   /*!< DS18B20 9 bits resolution */
  eDS18B20_RESOLUTION_10BITS = 10, /*!< DS18B20 10 bits resolution */
  eDS18B20_RESOLUTION_11BITS = 11, /*!< DS18B20 11 bits resolution */
  eDS18B20_RESOLUTION_12BITS = 12  /*!< DS18B20 12 bits resolution */
}TyeDS18B20_Resolution;

/**
  * @brief
  */
typedef struct {
  
  TysOneWire_Obj *one_wire;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint64_t rom;                 /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  char *name;                   /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
}TysCdrvDS18B20_Obj;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint8_t CdrvDS18B20_Start(TysCdrvDS18B20_Obj * const me);
uint8_t CdrvDS18B20_Read(TysCdrvDS18B20_Obj * const me, float* destination);
uint8_t CdrvDS18B20_GetResolution(TysCdrvDS18B20_Obj * const me, uint8_t *resolution);
uint8_t CdrvDS18B20_SetResolution(TysCdrvDS18B20_Obj * const me, TyeDS18B20_Resolution resolution);
uint8_t CdrvDS18B20_SetAlarmHighTemperature(TysCdrvDS18B20_Obj * const me, int8_t temp);
uint8_t CdrvDS18B20_SetAlarmLowTemperature(TysCdrvDS18B20_Obj * const me, int8_t temp);
uint8_t CdrvDS18B20_DisableAlarmTemperature(TysCdrvDS18B20_Obj * const me);

uint8_t CdrvDS18B20_AlarmSearch(TysOneWire_Obj * one_wire);
bool CdrvDS18B20_IsAllDone(TysOneWire_Obj * one_wire);
void CdrvDS18B20_StartAll(TysOneWire_Obj * one_wire);

bool CdrvDS18B20_Is(uint64_t rom);

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

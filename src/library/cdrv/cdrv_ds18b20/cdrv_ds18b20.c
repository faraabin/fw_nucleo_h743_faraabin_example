/**
 ******************************************************************************
 *  @file         prtl_mbc_rtu_eng.c
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
#include "cdrv_ds18b20.h"

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
  * @brief Initialize one_wire & temperature sensor & strat sensor conversion.
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_Start(TysCdrvDS18B20_Obj * const me) {
  
  /* Check if device is DS18B20 */
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Start temperature conversion */
  OneWire_WriteByte(me->one_wire, DS18B20_CMD_CONVERTTEMP);
  
  return 0;
}

/**
  * @brief Read converted value from a specific sensor.
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_Read(TysCdrvDS18B20_Obj * const me, float *destination) {
  
  uint16_t temperature;
  uint8_t resolution;
  int8_t digit, minus = 0;
  float decimal;
  uint8_t i = 0;
  uint8_t data[9];
  uint8_t crc;
  
  /* Check if device is DS18B20 */
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  
  /* Check if line is released, if it is, then conversion is complete */
  if (!OneWire_ReadBit(me->one_wire)) {
    /* Conversion is not finished yet */
    return 1; 
  }
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Read scratchpad command by one_wire protocol */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_RSCRATCHPAD);
  
  /* Get data */
  for (i = 0; i < 9; i++) {
    /* Read byte by byte */
    data[i] = OneWire_ReadByte(me->one_wire);
  }
  
  /* Calculate CRC */
  crc = OneWire_CRC8(data, 8);
  
  /* Check if CRC is ok */
  if (crc != data[8]) {
    /* CRC invalid */
    return 1;
  }
  
  /* First two bytes of scratchpad are temperature values */
  temperature = data[0] | (data[1] << 8);
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  
  /* Check if temperature is negative */
  if (temperature & 0x8000) {
    /* Two's complement, temperature is negative */
    temperature = ~temperature + 1;
    minus = 1;
  }
  
  
  /* Get sensor resolution */
  resolution = ((data[4] & 0x60) >> 5) + 9;
  
  
  /* Store temperature integer digits and decimal digits */
  digit = temperature >> 4;
  digit |= ((temperature >> 8) & 0x7) << 4;
  
  /* Store decimal digits */
  switch (resolution) {
  case 9: {
    decimal = (temperature >> 3) & 0x01;
    decimal *= (float)DS18B20_DECIMAL_STEPS_9BIT;
  } break;
  case 10: {
    decimal = (temperature >> 2) & 0x03;
    decimal *= (float)DS18B20_DECIMAL_STEPS_10BIT;
  } break;
  case 11: {
    decimal = (temperature >> 1) & 0x07;
    decimal *= (float)DS18B20_DECIMAL_STEPS_11BIT;
  } break;
  case 12: {
    decimal = temperature & 0x0F;
    decimal *= (float)DS18B20_DECIMAL_STEPS_12BIT;
  } break;
  default: {
    decimal = 0xFF;
    digit = 0;
  }
  }
  
  /* Check for negative part */
  decimal = digit + decimal;
  if (minus) {
    decimal = 0 - decimal;
  }
  
  /* Set to pointer */
  *destination = decimal;
  
  /* Return 0, temperature valid */
  return 0;
}

/**
  * @brief Get resolution from a specific sensor
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_GetResolution(TysCdrvDS18B20_Obj * const me, uint8_t *resolution) {
  
  uint8_t conf;
  
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Read scratchpad command by one_wire protocol */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_RSCRATCHPAD);
  
  /* Ignore first 4 bytes */
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  
  /* 5th byte of scratchpad is configuration register */
  conf = OneWire_ReadByte(me->one_wire);
  
  /* Return 9 - 12 value according to number of bits */
  *resolution = ((conf & 0x60) >> 5) + 9;
  
  return 0;
}

/**
  * @brief Set resolution to a specific sensor
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_SetResolution(TysCdrvDS18B20_Obj * const me, TyeDS18B20_Resolution resolution) {
  
  uint8_t th, tl, conf;
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Read scratchpad command by one_wire protocol */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_RSCRATCHPAD);
  
  /* Ignore first 2 bytes */
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  
  th = OneWire_ReadByte(me->one_wire);
  tl = OneWire_ReadByte(me->one_wire);
  conf = OneWire_ReadByte(me->one_wire);
  
  if (resolution == eDS18B20_RESOLUTION_9BITS) {
    conf &= ~(1 << DS18B20_RESOLUTION_R1);
    conf &= ~(1 << DS18B20_RESOLUTION_R0);
  } else if (resolution == eDS18B20_RESOLUTION_10BITS) {
    conf &= ~(1 << DS18B20_RESOLUTION_R1);
    conf |= 1 << DS18B20_RESOLUTION_R0;
  } else if (resolution == eDS18B20_RESOLUTION_11BITS) {
    conf |= 1 << DS18B20_RESOLUTION_R1;
    conf &= ~(1 << DS18B20_RESOLUTION_R0);
  } else if (resolution == eDS18B20_RESOLUTION_12BITS) {
    conf |= 1 << DS18B20_RESOLUTION_R1;
    conf |= 1 << DS18B20_RESOLUTION_R0;
  }
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Write scratchpad command by one_wire protocol, only th, tl and conf register can be written */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_WSCRATCHPAD);
  
  /* Write bytes */
  OneWire_WriteByte(me->one_wire, th);
  OneWire_WriteByte(me->one_wire, tl);
  OneWire_WriteByte(me->one_wire, conf);
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Copy scratchpad to EEPROM of DS18B20 */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_CPYSCRATCHPAD);
  
  return 0;
}

/**
  * @brief Config low temperature alarm to a specific sensor
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_SetAlarmLowTemperature(TysCdrvDS18B20_Obj * const me, int8_t temp) {
  
  uint8_t tl, th, conf;
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  if (temp > 125) {
    temp = 125;
  } 
  if (temp < -55) {
    temp = -55;
  }
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Read scratchpad command by one_wire protocol */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_RSCRATCHPAD);
  
  /* Ignore first 2 bytes */
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  
  th = OneWire_ReadByte(me->one_wire);
  tl = OneWire_ReadByte(me->one_wire);
  conf = OneWire_ReadByte(me->one_wire);
  
  tl = (uint8_t)temp; 
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Write scratchpad command by one_wire protocol, only th, tl and conf register can be written */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_WSCRATCHPAD);
  
  /* Write bytes */
  OneWire_WriteByte(me->one_wire, th);
  OneWire_WriteByte(me->one_wire, tl);
  OneWire_WriteByte(me->one_wire, conf);
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Copy scratchpad to EEPROM of DS18B20 */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_CPYSCRATCHPAD);
  
  return 0;
}

/**
  * @brief Config high temperature alarm to a specific sensor
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_SetAlarmHighTemperature(TysCdrvDS18B20_Obj * const me, int8_t temp) {
  
  uint8_t tl, th, conf;
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  if (temp > 125) {
    temp = 125;
  } 
  if (temp < -55) {
    temp = -55;
  }
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Read scratchpad command by one_wire protocol */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_RSCRATCHPAD);
  
  /* Ignore first 2 bytes */
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  
  th = OneWire_ReadByte(me->one_wire);
  tl = OneWire_ReadByte(me->one_wire);
  conf = OneWire_ReadByte(me->one_wire);
  
  th = (uint8_t)temp; 
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Write scratchpad command by one_wire protocol, only th, tl and conf register can be written */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_WSCRATCHPAD);
  
  /* Write bytes */
  OneWire_WriteByte(me->one_wire, th);
  OneWire_WriteByte(me->one_wire, tl);
  OneWire_WriteByte(me->one_wire, conf);
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Copy scratchpad to EEPROM of DS18B20 */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_CPYSCRATCHPAD);
  
  return 0;
}

/**
  * @brief Disable temperature alarm of a specific sensor.
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_DisableAlarmTemperature(TysCdrvDS18B20_Obj * const me) {
  uint8_t tl, th, conf;
  if (!CdrvDS18B20_Is(me->rom)) {
    return 1;
  }
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Read scratchpad command by one_wire protocol */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_RSCRATCHPAD);
  
  /* Ignore first 2 bytes */
  OneWire_ReadByte(me->one_wire);
  OneWire_ReadByte(me->one_wire);
  
  th = OneWire_ReadByte(me->one_wire);
  tl = OneWire_ReadByte(me->one_wire);
  conf = OneWire_ReadByte(me->one_wire);
  
  th = 125;
  tl = (uint8_t)-55;
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Write scratchpad command by one_wire protocol, only th, tl and conf register can be written */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_WSCRATCHPAD);
  
  /* Write bytes */
  OneWire_WriteByte(me->one_wire, th);
  OneWire_WriteByte(me->one_wire, tl);
  OneWire_WriteByte(me->one_wire, conf);
  
  /* Reset line */
  OneWire_Reset(me->one_wire);
  /* Select ROM number */
  OneWire_SelectWithPointer(me->one_wire, me->rom);
  /* Copy scratchpad to EEPROM of DS18B20 */
  OneWire_WriteByte(me->one_wire, ONEWIRE_CMD_CPYSCRATCHPAD);
  
  return 0;
}

/**
  * @brief 
  * @note  
  * @param  
  * @retval
*/
uint8_t CdrvDS18B20_AlarmSearch(TysOneWire_Obj * one_wire) {
  /* Start alarm search */
  return OneWire_Search(one_wire, DS18B20_CMD_ALARMSEARCH);
}

/**
  * @brief Check if converting of all sensor on bus is done ot not.
  * @note  
  * @param  
  * @retval
*/
bool CdrvDS18B20_IsAllDone(TysOneWire_Obj * one_wire) {
  /* If read bit is low, then device is not finished yet with calculation temperature */
  
  if(OneWire_ReadBit(one_wire) == 0) {
    return false;
  }
  
  return true;
}

/**
  * @brief Start all temperature sensor in one_wire bus.
  * @note  
  * @param  
  * @retval
*/
void CdrvDS18B20_StartAll(TysOneWire_Obj * one_wire) {
  
  /* Reset pulse */
  OneWire_Reset(one_wire);
  /* Skip rom */
  OneWire_WriteByte(one_wire, ONEWIRE_CMD_SKIPROM);
  /* Start conversion on all connected devices */
  OneWire_WriteByte(one_wire, DS18B20_CMD_CONVERTTEMP);
}

/**
  * @brief Check existance of a specific sensor.
  * @note  
  * @param  
  * @retval
*/
bool CdrvDS18B20_Is(uint64_t rom) {
  
  Tyu_8Byte tmp;
  
  tmp.u64 = rom;
  
  /* Checks if first byte is equal to DS18B20's family code */
  if (tmp.byte[0] == DS18B20_FAMILY_CODE) {
    return true;
  }
  return false;
}

/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

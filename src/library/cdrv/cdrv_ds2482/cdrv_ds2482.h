/**
******************************************************************************
* @file           : cdrv_ds2482.h
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2023 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2023 FaraabinCo.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __cdrv_ds2482_H
#define __cdrv_ds2482_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "hal\phal\intf\me_hal_i2c_intf.h"
#include "hal\phal\intf\me_hal_gpio_intf.h"

/* Exported defines ----------------------------------------------------------*/
/*
 * One wire commands
 */
#define ONEWIRE_CMD_RSCRATCHPAD     0xBE
#define ONEWIRE_CMD_WSCRATCHPAD     0x4E
#define ONEWIRE_CMD_CPYSCRATCHPAD   0x48
#define ONEWIRE_CMD_RECEEPROM       0xB8
#define ONEWIRE_CMD_RPWRSUPPLY      0xB4
#define ONEWIRE_CMD_SEARCHROM       0xF0
#define ONEWIRE_CMD_READROM         0x33
#define ONEWIRE_CMD_MATCHROM        0x55
#define ONEWIRE_CMD_SKIPROM         0xCC

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum {
  eCONFIG_NONE = 0x00U,
  eCONFIG_APU = 0x01U,
  eCONFIG_SPU = 0x04U,
  eCONFIG_1WS = 0x08U
}eCdrvDs2482_Config;

typedef struct {
  INHERITE_(TysObj)           /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  TysI2c_Obj *I2c;            /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint32_t I2cTimeout_ms;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _deviceAddress;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _deviceStatus;      /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _deviceConfig;      /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t _txData[2];         /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  eCdrvDs2482_Config Config;  /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
  
  uint8_t LastDiscrepancy;    /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t LastFamilyDiscrepancy; /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t LastDeviceFlag;     /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */

  uint8_t ROM_NO[8];          /*!< Specifies the ---.
                               This parameter can be a value of @ref ---
                               @note . */
}sCdrvDs2482Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvDs2482_Init(sCdrvDs2482Obj * const me, uint8_t addr);
uint8_t fCdrvDs2482_Reset(sCdrvDs2482Obj * const me);
uint8_t fCdrvDs2482_WriteConfig(sCdrvDs2482Obj * const me, uint8_t config);

uint8_t fCdrvDs2482_OneWireReset(sCdrvDs2482Obj * const me);
uint8_t fCdrvDs2482_OneWireWriteBit(sCdrvDs2482Obj * const me, uint8_t sendbit);
uint8_t fCdrvDs2482_OneWireReadBit(sCdrvDs2482Obj * const me);
uint8_t fCdrvDs2482_OneWireTouchBit(sCdrvDs2482Obj * const me, uint8_t sendbit);
uint8_t fCdrvDs2482_OneWireWriteByte(sCdrvDs2482Obj * const me, uint8_t sendbyte);
uint8_t fCdrvDs2482_OneWireReadByte(sCdrvDs2482Obj * const me);
uint8_t fCdrvDs2482_OneWireBlock(sCdrvDs2482Obj * const me, uint8_t *tran_buf, uint16_t tran_len);
uint8_t fCdrvDs2482_OneWireTouchByte(sCdrvDs2482Obj * const me, uint8_t sendbyte);
int fCdrvDs2482_OneWireFirst(sCdrvDs2482Obj * const me);
int fCdrvDs2482_OneWireNext(sCdrvDs2482Obj * const me);
int fCdrvDs2482_OneWireSearch(sCdrvDs2482Obj * const me, uint8_t cmd);
uint8_t fCdrvDs2482_OneWireSearchTriplet(sCdrvDs2482Obj * const me, uint8_t search_direction);

uint16_t fCdrvDs2482_OneWireScan(sCdrvDs2482Obj * const me, uint16_t max_device, uint64_t *deviceRom);
void fCdrvDs2482_Select(sCdrvDs2482Obj * const me, uint8_t* addr);
void fCdrvDs2482_SelectWithPointer(sCdrvDs2482Obj * const me, uint8_t *rom);
uint8_t OneWire_CRC8(uint8_t *addr, uint8_t len);
void OneWire_GetFullROM(sCdrvDs2482Obj * const me, uint8_t *firstIndex);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_DS2482_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

/**
 ******************************************************************************
 * @file           : cdrv_w25n.h
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 FaraabinCo.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component
 * 
 * https://faraabinco.ir/
 * https://github.com/FaraabinCo
 *
 ******************************************************************************
 * @verbatim
 * @endverbatim
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef cdrv_w25n_H
#define cdrv_w25n_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/  
#include "cdrv_w25n_private.h"

#include "i_gpio.h"
#include "i_spi.h"
#include "i_memory.h"

#include "chrono.h"

#include <stdint.h>
#include <stdbool.h>

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 * @brief 
 * 
 */
typedef enum {
  
  eW25N01GV,
  eW25M02GV,
	eW25N04KV,
  
}eCdrvW25Nxx_Chip;

/**
 * @brief 
 * 
 */
typedef struct {
  
  bool _init;               /*!< . */

  bool Enable;              /*!< . */
  
  sChrono _timer;           /*!< . */
  
  eCdrvW25Nxx_Chip _chip;   /*!< . */
  
  uint16_t _pageSize;       /*!< . */
  
  uint8_t _addrByteQty;     /*!< . */
  
  sGpio *Wp;                /*!< . */
  
  sGpio *Cs;                /*!< . */
  
  sSpi *Spi;                /*!< . */
                               
  uint32_t SpiTimeoutMs;    /*!< . */
                               
  uint8_t _rxBuffer[2048];  /*!< . */
  
  uint8_t _dieSelect;       /*!< . */

}sCdrvW25Nxx;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvW25Nxx_Init(sCdrvW25Nxx * const me, eCdrvW25Nxx_Chip chip);
sMemory* fCdrvW25Nxx_CreatePartition(sCdrvW25Nxx * const me, uint32_t start_addr, uint32_t size);
uint8_t fCdrvW25Nxx_WpDisable(sCdrvW25Nxx * const me);
uint8_t fCdrvW25Nxx_WpEnable(sCdrvW25Nxx * const me);
uint32_t fCdrvW25Nxx_GetSize(sCdrvW25Nxx * const me);

int w25n_begin(sCdrvW25Nxx * const me);
void w25n_reset(sCdrvW25Nxx * const me);
int w25n_dieSelect(sCdrvW25Nxx * const me, uint8_t die);
int w25n_dieSelectOnAdd(sCdrvW25Nxx * const me, uint32_t pageAdd);
char w25n_getStatusReg(sCdrvW25Nxx * const me, char reg);
void w25n_setStatusReg(sCdrvW25Nxx * const me, char reg, char set);
uint32_t w25n_getMaxPage(sCdrvW25Nxx * const me);
void w25n_writeEnable(sCdrvW25Nxx * const me);
void w25n_writeDisable(sCdrvW25Nxx * const me);
int w25n_blockErase(sCdrvW25Nxx * const me, uint32_t pageAdd);
int w25n_bulkErase(sCdrvW25Nxx * const me);
int w25n_writeToInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen);
int w25n_writeRandToInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen);
int w25n_writeInternalBufferToPage(sCdrvW25Nxx * const me, uint32_t pageAdd);
int w25n_readPageToInternalBuffer(sCdrvW25Nxx * const me, uint32_t pageAdd);
int w25n_readInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen);
int w25n_verifyByInternalBuffer(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen);
int w25n_check_WIP(sCdrvW25Nxx * const me);
int w25n_block_WIP(sCdrvW25Nxx * const me, uint32_t timeout_ms);
int w25n_check_status(sCdrvW25Nxx * const me);

int w25n_write_page(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd);
int w25n_read_page(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd);
int w25n_verify_page(sCdrvW25Nxx * const me, uint16_t columnAdd, uint8_t* buf, uint32_t dataLen, uint32_t pageAdd);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CDRV_W25N_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

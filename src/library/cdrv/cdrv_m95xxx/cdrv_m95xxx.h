/**
 ******************************************************************************
 * @file           : cdrv_m95xxx.h
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
#ifndef cdrv_m95xxx_H
#define cdrv_m95xxx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "i_memory.h"
#include "i_gpio.h"
#include "i_spi.h"

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

  eDEVICE_M95080,
  eDEVICE_M95640,
  eDEVICE_M95M01
  
}eCdrvM95xxxChip;

/**
 * @brief 
 * 
 */
typedef struct {
  
  bool _init;             /*!< . */
  
  bool Enable;            /*!< . */
   
  sChrono _timer;         /*!< . */
  
  eCdrvM95xxxChip _chip;  /*!< . */
  
  uint8_t *_tmpBuffer;    /*!< . */
  
  uint16_t _pageSize;     /*!< . */
  
  uint8_t _addrByteQty;   /*!< . */
  
  sGpio *Wp;              /*!< . */
  
  sGpio *Cs;              /*!< . */
  
  sSpi *Spi;              /*!< . */
                               
  uint32_t SpiTimeoutMs;  /*!< . */

}sCdrvM95xxx;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvM95xxx_Init(sCdrvM95xxx * const me, eCdrvM95xxxChip chip);
sMemory* fCdrvM95xxx_CreatePartirion(sCdrvM95xxx * const me, uint32_t start_addr, uint32_t size);
uint8_t fCdrvM95xxx_WpDisable(sCdrvM95xxx * const me);
uint8_t fCdrvM95xxx_WpEnable(sCdrvM95xxx * const me);
uint32_t fCdrvM95xxx_GetSize(sCdrvM95xxx * const me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CDRV_M95XXX_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

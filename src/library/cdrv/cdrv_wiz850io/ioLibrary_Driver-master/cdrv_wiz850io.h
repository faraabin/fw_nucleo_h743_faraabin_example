/**
 ******************************************************************************
 * @file           : cdrv_wiz850io.h
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
#ifndef cdrv_wiz850io_H
#define cdrv_wiz850io_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "i_tcp_server.h"
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

   eIP_MODE_STATIC = 1,
   eIP_MODE_DHCP

}eCdrvWiz850io_IpMode;

/**
 * @brief 
 * 
 */
typedef struct {
  
  bool _init;             /*!< . */
  
  bool Enable;            /*!< . */
   
  sGpio *Cs;              /*!< . */
  
  sSpi *Spi;              /*!< . */
                               
  uint32_t SpiTimeoutMs;  /*!< . */

}sCdrvWiz850io;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvWiz850io_Init(sCdrvWiz850io * const me);
void fCdrvWiz850io_Run(sCdrvWiz850io * const me);
uint8_t fCdrvWiz850io_SetNetInfo(sCdrvWiz850io * const me, 
  eCdrvWiz850io_IpMode ipMode, 
  uint8_t *mac,
  uint8_t *ip,
  uint8_t *subnetMask,
  uint8_t *gateway,
  uint8_t *dns);

sTcpServer* fCdrvWiz850io_CreateTcpServer(sCdrvWiz850io * const me, uint8_t socketNo, uint8_t *pBuffer, uint32_t bufferSize);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CDRV_WIZ850IO_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

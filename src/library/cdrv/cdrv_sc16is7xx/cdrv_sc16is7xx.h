/**
******************************************************************************
* @file           : cdrv_sc16is7xx.h
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
#ifndef __cdrv_sc16is7xx_H
#define __cdrv_sc16is7xx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"
#include "library\type\me_obj.h"

#include "hal\phal\intf\me_hal_gpio_intf.h"
#include "hal\phal\intf\me_hal_serial_intf.h"
#include "hal\phal\intf\me_hal_spi_intf.h"
#include "library\chrono\me_chrono.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief
  */
typedef struct {
  INHERITE_(TysObj)           /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  float OscillatorClockMhz;   /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  TysSerial_Obj Uart;         /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  TysSpi_Obj *Spi;            /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  TysGpio_Obj *SpiCs;         /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  TysGpio_Obj *Reset;         /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  TysGpio_Obj *Irq;           /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  uint32_t SpiTimeout;        /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  uint8_t RxFifoTrigLevel;    /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  void(*fpEventSendEnd)(void);  /*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  void(*fpEventReceiveByte)(uint8_t);/*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  void(*fpEventIdleDetection)(void);/*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  void(*fpEventError)(void*, uint32_t);/*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  void(*fpEventReceiveBufferOvf)(uint8_t*, uint16_t);/*!< Specifies the ---.
                            This parameter can be a value of @ref ---
                            @note . */

  uint16_t _receiveQty;
  uint16_t _rxRemainSize;
  uint16_t _txRemainSize;
  uint16_t _txSentIndex;
  uint8_t *_txDataPtr;
  uint16_t _txLastSentSize;
  uint8_t _txIsBlocking;
  uint8_t _iirState;
  TysChrono_Obj _swIdleDetectionChrono;
  float _swIdleDetectionTimeout_us;
}sCdrvSc16is7xx_Obj;

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fCdrvSc16is7xx_Init(sCdrvSc16is7xx_Obj * const me);
uint8_t fCdrvSc16is7xx_Reset(sCdrvSc16is7xx_Obj * const me);

void fCdrvSc16is7xx_IrqHandler(sCdrvSc16is7xx_Obj *me);
void fCdrvSc16is7xx_SoftwareIdleDetection_Run(sCdrvSc16is7xx_Obj *me);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CDRV_SC16IS7XX_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

/**
******************************************************************************
* @file           : mtssp.h
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
#ifndef __mtssp_H
#define __mtssp_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

/* Exported defines ----------------------------------------------------------*/
/*! \brief Opcode to write to control pipe in I2C/SPI mode */
#define XBUS_PROTOCOL_INFO (0x01)
#define XBUS_CONFIGURE_PROTOCOL (0x02)
#define XBUS_CONTROL_PIPE (0x03)
#define XBUS_PIPE_STATUS (0x04)
#define XBUS_NOTIFICATION_PIPE (0x05)
#define XBUS_MEASUREMENT_PIPE (0x06)

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** 
  * @brief
  */
struct sMtsspVtbl;

/** 
  * @brief
  */
typedef struct {
	
	struct sMtsspVtbl const *IntfFptr;
	void *_devPvt;
	
}sMtsspIntf;

struct sMtsspVtbl{
	void(*Write)(sMtsspIntf * const me, uint8_t opcode, uint8_t const * data, int length);
	void(*Read)(sMtsspIntf * const me, uint8_t opcode, uint8_t const * data, int length);
	void(*WriteRaw)(sMtsspIntf * const me, uint8_t const * data, int length);
};

/* Exported constants --------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint8_t fMtssp_Init(sMtsspIntf * const me);
void fMtssp_ReadProtocolInfo(sMtsspIntf * const me, uint8_t *version, uint8_t *dReadyConfig);
void fMtssp_ConfigureProtocol(sMtsspIntf * const me, uint8_t dReadyConfig);
void fMtssp_ReadPipeStatus(sMtsspIntf * const me, uint16_t *notificationMessageSize, uint16_t *measurementMessageSize);
void fMtssp_ReadFromPipe(sMtsspIntf * const me, uint8_t* buffer, uint16_t size, uint8_t pipe);
size_t fMtssp_CreateRawMessage(sMtsspIntf * const me, uint8_t* dest, uint8_t const* message);
void fMtssp_SendXbusMessage(sMtsspIntf * const me, uint8_t const* xbusMessage);

/* Exported variables --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __MTSSP_H */

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

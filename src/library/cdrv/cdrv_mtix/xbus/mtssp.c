/**
******************************************************************************
* @file           : mtssp.c
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

/* Includes ------------------------------------------------------------------*/
#include "mtssp.h"
#include "xbus.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static bool init;

/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                  ##### mtssp.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fMtssp_Init(sMtsspIntf * const me) {
	init = false;
	
	if((me->IntfFptr->Read == NULL) ||
		 (me->IntfFptr->Write == NULL) ||
		 (me->IntfFptr->WriteRaw == NULL)) {
			return 1; 
	 }
	
	init = true;
	return 0;
}
/*!	\brief Read MTSSP protocol info
	\param[out] version: The version byte
	\param[out] dataReadyConfig: The data ready configuration byte
	\sa configureProtocol
*/
void fMtssp_ReadProtocolInfo(sMtsspIntf * const me, uint8_t *version, uint8_t *dReadyConfig) {
	uint8_t buffer[2];
	
	if(!init) {
		return;
	}
	
	me->IntfFptr->Read(me, XBUS_PROTOCOL_INFO, buffer, 2);
	*version = buffer[0];
	*dReadyConfig = buffer[1];
}

/*!	\brief Write MTSSP protocol settings
	\param[in] dataReadyConfig The data ready configuration which must be set

	Bit 7:4	Reserved \n
	Bit 3	Measurement pipe DRDY event enable: 0 = disabled, 1 = enabled \n
	Bit 2	Notification pipe DRDY event enable: 0 = disabled, 1 = enabled \n
	Bit 1	Output type of DRDY pin: = 0 Push/pull, 1 = open drain \n
	Bit 0	Polarity of DRDY signal: 0 = Idle low, 1 = Idle high \n
	\sa readProtocolInfo
*/
void fMtssp_ConfigureProtocol(sMtsspIntf * const me, uint8_t dReadyConfig) {
	uint8_t data = dReadyConfig;
	
	if(!init) {
		return;
	}
	
	me->IntfFptr->Write(me, XBUS_CONFIGURE_PROTOCOL, &data, 1);
}

/*!	\brief Read the pipe status
	\param[out] notificationMessageSize: The number of pending notification bytes
	\param[out] measurementMessageSize: The number of pending measurement bytes
*/
void fMtssp_ReadPipeStatus(sMtsspIntf * const me, uint16_t *notificationMessageSize, uint16_t *measurementMessageSize) {
	uint8_t status[4];
	
	if(!init) {
		return;
	}
	
	me->IntfFptr->Read(me, XBUS_PIPE_STATUS, status, sizeof(status));
	*notificationMessageSize = status[0] | (status[1] << 8);
	*measurementMessageSize = status[2] | (status[3] << 8);
}

/*!	\brief Read from notification or measurement data pipe
	\param[out] buffer Result buffer
	\param[in] size Number of bytes to read
	\param[in] pipe Pipe from which to read, XBUS_NOTIFICATION_PIPE or XBUS_MEASUREMENT_PIPE
*/
void fMtssp_ReadFromPipe(sMtsspIntf * const me, uint8_t* buffer, uint16_t size, uint8_t pipe) {
	if(!init) {
		return;
	}
	
	if((pipe == XBUS_NOTIFICATION_PIPE) || (pipe == XBUS_MEASUREMENT_PIPE)) {
		me->IntfFptr->Read(me, pipe, buffer, size);
	}
}

/*!	\brief Format a message into the raw mtssp format ready for transmission to a motion tracker.
*/
size_t fMtssp_CreateRawMessage(sMtsspIntf * const me, uint8_t* dest, uint8_t const* message) {
	int n;
	uint8_t checksum;
	uint16_t length;
	uint8_t* dptr = dest;
	
	if(!init) {
		return 0;
	}

	length = Xbus_getPayloadLength(message);

	//TODO: Right now only SPI format is implemented
	if (dest == 0)
	{
//		switch (format)
//		{
//		case XBF_I2c:
//			return (length < 255) ? length + 4 : length + 6;
//		case XBF_Spi:
			return (length < 255) ? length + 7 : length + 9;
//		case XBF_Uart:
//			return (length < 255) ? length + 5 : length + 7;
//		}
	}

	//TODO: Right now only SPI format is implemented
//	switch (format)
//	{
//	case XBF_I2c:
//		*dptr++ = XBUS_CONTROL_PIPE;
//		break;

//	case XBF_Spi:
		*dptr++ = XBUS_CONTROL_PIPE;
		// Fill bytes required to allow MT to process data
		*dptr++ = 0;
		*dptr++ = 0;
		*dptr++ = 0;
//		break;

//	case XBF_Uart:
//		*dptr++ = XBUS_PREAMBLE;
//		*dptr++ = XBUS_MASTERDEVICE;
//		break;
//	}

	checksum = 0;
	checksum -= XBUS_MASTERDEVICE;

	*dptr = Xbus_getMessageId(message);
	checksum -= *dptr++;

	if (length < XBUS_EXTENDED_LENGTH)
	{
		*dptr = length;
		checksum -= *dptr++;
	}
	else
	{
		*dptr = XBUS_EXTENDED_LENGTH;
		checksum -= *dptr++;
		*dptr = length >> 8;
		checksum -= *dptr++;
		*dptr = length & 0xFF;
		checksum -= *dptr++;
	}

	for (n = 0; n < length; n++)
	{
		*dptr = Xbus_getConstPointerToPayload(message)[n];
		checksum -= *dptr++;
	}

	*dptr++ = checksum;

	return dptr - dest;
}

/*! \brief Sends an xbus message to the motion tracker
	\param[in] xbusMessage Pointer to xbus message which should be send
*/
void fMtssp_SendXbusMessage(sMtsspIntf * const me, uint8_t const* xbusMessage) {
	uint8_t buffer[128];
	
	if(!init) {
		return;
	}
	
	size_t rawLength = fMtssp_CreateRawMessage(me, buffer, xbusMessage);
	me->IntfFptr->WriteRaw(me, buffer, rawLength);
}

/*
===============================================================================
                  ##### mtssp.c Private Functions #####
===============================================================================*/


/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

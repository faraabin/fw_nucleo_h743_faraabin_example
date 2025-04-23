/**
******************************************************************************
* @file           : cdrv_mtix.c
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
#include "cdrv_mtix.h"
#include "stdlib.h"
#include "string.h"
#include "xbus\xbus.h"
#include "xbus\xbusmessageid.h"

/* Private define ------------------------------------------------------------*/
/*Output Configuration*/
/*XDI_TimeStampGroup*/
#define MTi1_XDI_PacketCounter 					(uint16_t)0x1020
#define MTi1_XDI_SampleTimeFine 				(uint16_t)0x1060
#define MTi1_XDI_SampleTimeCoarse				(uint16_t)0x1070
/*XDI_OrientationGroup*/
#define MTi1_XDI_Quaternion 						(uint16_t)0x2010
#define MTi1_XDI_RotationMatrix 				(uint16_t)0x2020
#define MTi1_XDI_EulerAngles 						(uint16_t)0x2030
/*XDI_AccelerationGroup*/
#define MTi1_XDI_DeltaV 								(uint16_t)0x4010
#define MTi1_XDI_Acceleration 					(uint16_t)0x4020
#define MTi1_XDI_FreeAcceleration 			(uint16_t)0x4030
#define MTi1_XDI_AccelerationHR 				(uint16_t)0x4040
/*XDI_AngularVelocityGroup*/
#define MTi1_XDI_RateOfTurn 						(uint16_t)0x8020
#define MTi1_XDI_DeltaQ 								(uint16_t)0x8030
#define MTi1_XDI_RateOfTurnHR 					(uint16_t)0x8040
/*XDI_MagneticGroup*/
#define MTi1_XDI_MagneticField 					(uint16_t)0xC020
/*XDI_StatusGroup*/
#define MTi1_XDI_StatusWord 						(uint16_t)0xE020
#define MTi1_XDI_StatusByte 						(uint16_t)0xE010

#define MTi1_MID_SetOutputConfiguration	(uint8_t)0xC0
#define MTi1_MID_GoToConfig							(uint8_t)0x30
#define MTi1_MID_GoToMeasurement				(uint8_t)0x10
#define MTi1_MID_SetNoRotation					(uint8_t)0x22
#define MTi1_MID_IccCommand							(uint8_t)0x74

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t MtixZeroInitObj(sMTix_Object * const me);
static void SpiWrite(sMtsspIntf * const me, uint8_t opcode, uint8_t const * data, int length);
static void SpiRead(sMtsspIntf * const me, uint8_t opcode, uint8_t const * data, int length);
static void SpiWriteRaw(sMtsspIntf * const me, uint8_t const * data, int length);

static void HandleMessage(sMTix_Object * const me, uint8_t *data, uint16_t messageSize);

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                ##### cdrv_mti7.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMtix_Init(sMTix_Object * const me, sMTixDataReadyConfig dataReadyConfig) {
	uint8_t drdy, version;
	
	me->_init = false;
	
	MtixZeroInitObj(me);
	if(me->Spi == NULL) {
		return 1;
	}
	me->Spi->u_bit_order = eSPI_FIRSTBIT_MSB;
	me->Spi->u_data_size = 8;
	me->Spi->u_mode = eSPI_MODE_3;
	me->Spi->u_role = eSPI_ROLE_MASTER;
	if(meSpi_Init_(me->Spi) != 0) {
		return 1;
	}
	
	if(me->Cs == NULL) {
		return 1;
	}
	me->Cs->u_dir = eGPIO_DIR_OUTPUT;
	me->Cs->u_out_type = eGPIO_PUSH_PULL;
	if(meGpio_Init_(me->Cs) != 0) {
		return 1;
	}
	meGpio_Set_(me->Cs);
	
	if(me->Drdy == NULL) {
		return 1;
	}
	me->Drdy->u_dir = eGPIO_DIR_INPUT;
	me->Drdy->u_in_type = eGPIO_PULL_NONE;
	if(meGpio_Init_(me->Drdy) != 0) {
		return 1;
	}
	
	if(me->Reset != NULL) {
		me->Reset->u_dir = eGPIO_DIR_OUTPUT;
		me->Reset->u_out_type = eGPIO_PUSH_PULL;
		if(meGpio_Init_(me->Reset) != 0) {
			return 1;
		}
		meGpio_Set_(me->Reset);
	}
	
	if(fCdrvMtix_Reset(me, eMTIx_RESET_HARDWARE) != 0) {
		fCdrvMtix_Reset(me, eMTIx_RESET_SOFTWARE);
	}
	
	static struct sMtsspVtbl const vtbl = {
		SpiWrite,
		SpiRead,
		SpiWriteRaw
	};
	
	me->_mtssp.IntfFptr = &vtbl;
	me->_mtssp._devPvt = (void*)me;
	fMtssp_Init(&me->_mtssp);
	
	memcpy(&drdy, &dataReadyConfig, 1);
	fMtssp_ConfigureProtocol(&me->_mtssp, drdy);
	fMtssp_ReadProtocolInfo(&me->_mtssp, &version, &drdy);
	if(memcmp(&drdy, &dataReadyConfig, 1) != 0) {
		return 1;
	}
	
	me->_init = true;
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMtix_Reset(sMTix_Object * const me, eMTixResetType resetType) {
	
	switch(resetType) {
		case eMTIx_RESET_HARDWARE: {
			if(me->Reset == NULL) {
				return 1;
			}
			
			meGpio_Reset_(me->Reset);
			meDelay_ms_(1);
			meGpio_Set_(me->Reset);
		}
		case eMTIx_RESET_SOFTWARE: {
			Xbus_message(me->_txData, 0xFF, XMID_Reset, 0);
			fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
		}
		default:
			break;
	}
	
	return 0;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t fCdrvMtix_IsDataReady(sMTix_Object * const me) {
	uint8_t tmp = 0;
	
	meGpio_Read_(me->Drdy, &tmp);
	return tmp;
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_GoToConfig(sMTix_Object * const me) {
	Xbus_message(me->_txData, 0xFF, XMID_GotoConfig, 0);
	fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_GoToMeasurement(sMTix_Object * const me) {
	Xbus_message(me->_txData, 0xFF, XMID_GotoMeasurement, 0);
	fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestDeviceId(sMTix_Object * const me) {
	Xbus_message(me->_txData, 0xFF, XMID_ReqDid, 0);
	fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestProductCode(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestHardwareVersion(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestFirmwareRevision(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RunSelfTest(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestOptionFlags(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_SetOptionFlags(sMTix_Object * const me, eMTixOptionFlagsObj setFlags, eMTixOptionFlagsObj clearFlags) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RestoreFactory(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestConfig(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_RequestOutputConfig(sMTix_Object * const me) {
	//TODO:
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_SetOutputConfig(sMTix_Object * const me, sMTixOutputConfigObj config) {
	uint8_t frameLen = 0;
	int index = 0;
	
	fCdrvMtix_GoToConfig(me);
	meDelay_ms_(10);
	
	//TODO: Some of the configs are not implemented!
	if(config.ActivatePacketCounter) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x10;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
	}
	if(config.ActivateSampleTimeFine) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x10;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x60;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
	}
	if(config.ActivateSampleTimeCoarse) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x10;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x70;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
	}
	if(config.ActivateOrientationQuaternion) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x10;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.OrientationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.OrientationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateOrientationRotationMatrix) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.OrientationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.OrientationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateOrientationEulerAngles) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x30;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.OrientationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.OrientationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateDeltaV) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x40;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x10;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateAcceleration) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x40;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateFreeAcceleration) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x40;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x30;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateAccelerationHR) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x40;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x40;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AccelerationUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateRateOfTurn) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x80;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AngularVelocityUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AngularVelocityUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateDeltaQ) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x80;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x30;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AngularVelocityUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AngularVelocityUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateRateOfTurnHR) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x80;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x40;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AngularVelocityUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.AngularVelocityUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateMagneticField) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xC0;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.MagneticFieldUpdateRate >> 8) & 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = (config.MagneticFieldUpdateRate >> 0) & 0xFF;
	}
	if(config.ActivateStatusByte) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xE0;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x10;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
	}
	if(config.ActivateStatusWord) {
		frameLen += 4;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xE0;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0x20;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
		Xbus_getPointerToPayload(me->_txData)[index++] = 0xFF;
	}
	
	Xbus_message(me->_txData, 0xFF, XMID_SetOutputConfig, frameLen);
	fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
	
	fCdrvMtix_GoToMeasurement(me);
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_ReadFromDevice(sMTix_Object * const me) {
	uint16_t notificationMessageSize;
	uint16_t measurementMessageSize;
	
	fMtssp_ReadPipeStatus(&me->_mtssp, &notificationMessageSize, &measurementMessageSize);
	
	me->_rxData[0] = XBUS_PREAMBLE;
	me->_rxData[1] = XBUS_MASTERDEVICE;
	
	if(notificationMessageSize && notificationMessageSize < sizeof(me->_rxData)) {
		fMtssp_ReadFromPipe(&me->_mtssp, &me->_rxData[2], notificationMessageSize, XBUS_NOTIFICATION_PIPE);
		HandleMessage(me, me->_rxData, notificationMessageSize);
	}
	
	if (measurementMessageSize && measurementMessageSize < sizeof(me->_rxData)) {
		fMtssp_ReadFromPipe(&me->_mtssp, &me->_rxData[2], measurementMessageSize, XBUS_MEASUREMENT_PIPE);
		HandleMessage(me, me->_rxData, measurementMessageSize);
	}
}

/**
 * @brief 
 * 
 * @param me 
 */
void fCdrvMtix_SetNoRotation(sMTix_Object * const me, uint16_t delay_s) {
	uint8_t frameLen = 2;
	int index = 0;
	
	Xbus_getPointerToPayload(me->_txData)[index++] = delay_s >> 8;
	Xbus_getPointerToPayload(me->_txData)[index++] = (uint8_t)delay_s;
	
	Xbus_message(me->_txData, 0xFF, XMID_SetNoRotation, frameLen);
	fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
}

/**
 * @brief 
 * 
 * @param me 
 * @param cmd 
 */
void fCdrvMtix_InRunCompassCalibration(sMTix_Object * const me, eMTixInRunCompassCalibration cmd) {
	uint8_t frameLen = 1;
	int index = 0;
	
	if(cmd == eMTIx_IRCC_STORE_ICC_PARAM) {
		fCdrvMtix_GoToConfig(me);
	}
	
	Xbus_getPointerToPayload(me->_txData)[index++] = cmd;
	
	Xbus_message(me->_txData, 0xFF, XMID_InRunCompassCalib, frameLen);
	fMtssp_SendXbusMessage(&me->_mtssp, me->_txData);
	
	if(cmd == eMTIx_IRCC_STORE_ICC_PARAM) {
		fCdrvMtix_GoToMeasurement(me);
	}
}

/*
===============================================================================
                ##### cdrv_mtix.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
static uint8_t MtixZeroInitObj(sMTix_Object * const me) {
	
	memset(me->_rxData, 0x00, sizeof(me->_rxData));
	memset(me->_txData, 0x00, sizeof(me->_txData));
	memset(&me->Data, 0x00, sizeof(sMTi1DataObj));
	
	return 0;
}

/*!	\brief Perform a blocking write transfer on the SPI bus
	\param[in] opcode Opcode to use
	\param[in] data Pointer to data to be written
	\param[in] dataLength Number of data bytes to write
*/
static void SpiWrite(sMtsspIntf * const me, uint8_t opcode, uint8_t const * data, int length) {
	sMTix_Object *pvt = (sMTix_Object*)me->_devPvt;
	uint8_t buffer[4] = {0x00};
	
	meGpio_Reset_(pvt->Cs);
	
	meDelay_us_(4);
	buffer[0] = opcode;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
	meSpi_Transmit_(pvt->Spi, buffer, 4, pvt->SpiTimeout_ms);
	meSpi_Transmit_(pvt->Spi, (uint8_t *)data, length, pvt->SpiTimeout_ms);
	meDelay_us_(4);
	
	meGpio_Set_(pvt->Cs);
	
}

/*!	\brief Perform a blocking read transfer on the SPI bus
	\param[in] opcode Opcode to use
	\param[out] data Pointer to result buffer
	\param[in] dataLength Number of data bytes to read
*/
static void SpiRead(sMtsspIntf * const me, uint8_t opcode, uint8_t const * data, int length) {
	sMTix_Object *pvt = (sMTix_Object*)me->_devPvt;
	uint8_t buffer[4];
	
	meGpio_Reset_(pvt->Cs);
	
	meDelay_us_(4);
	buffer[0] = opcode;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
	meSpi_Transmit_(pvt->Spi, buffer, 4, pvt->SpiTimeout_ms);
	meSpi_Receive_(pvt->Spi, (uint8_t *)data, length, pvt->SpiTimeout_ms);
	meDelay_us_(4);
	
	meGpio_Set_(pvt->Cs);
	
}

/*!	\brief Perform a blocking write transfer on the SPI bus
	\param[in] data Pointer to data to be written
	\param[in] dataLength Number of data bytes to write
*/
static void SpiWriteRaw(sMtsspIntf * const me, uint8_t const * data, int length) {
	sMTix_Object *pvt = (sMTix_Object*)me->_devPvt;
	
	meGpio_Reset_(pvt->Cs);
	
	meDelay_us_(4);
	meSpi_Transmit_(pvt->Spi, (uint8_t *)data, length, pvt->SpiTimeout_ms);
	meDelay_us_(4);
	
	meGpio_Set_(pvt->Cs);
}

/**
 * @brief 
 * 
 * @param data 
 */
static void HandleMessage(sMTix_Object * const me, uint8_t *data, uint16_t messageSize) {
	uint8_t messageId = Xbus_getMessageId(data);
	
	if(messageId == XMID_Wakeup) {
		//TODO: Print
		if(me->wakeupCallback != NULL) {
			me->wakeupCallback();
		}
	}
	
	if(messageId == XMID_DeviceId) {
		Tyu_4Byte devId;
		int index = 4;
		devId.u32 = 0;
		
		devId.byte[3] = data[index++];
		devId.byte[2] = data[index++];
		devId.byte[1] = data[index++];
		devId.byte[0] = data[index++];
		
		if(me->reqDevIdCallback != NULL) {
			me->reqDevIdCallback(devId.u32);
		}
	}
	
	if(messageId == XMID_FirmwareRevision) {
//		int index = 4;
		
		if(me->reqFwRevisionCallback != NULL) {
			me->reqFwRevisionCallback(data, 3);
		}
	}
	
	if(messageId == XMID_OutputConfig) {
		//TODO:
	}
	
	if(messageId == XMID_IccCommandAck) {
		int index = 4;
		uint8_t iccData[7] = {0x00};
		uint8_t iccDataSize = data[index++];
		
		for(int i = 0; i < iccDataSize; i++) {
			iccData[i] = data[index++];
		}
		
		if(me->iccCommandAckCallback != NULL) {
			me->iccCommandAckCallback(iccData, iccDataSize);
		}
	}
	
	if(messageId == XMID_MtData2) {
		Tyu_2Byte dataId;
		uint8_t dataSize = 0;
		uint8_t frameSize = data[3];
		
		for(int index = 4; index < frameSize; ) {
			dataId.byte[1] = data[index++];
			dataId.byte[0] = data[index++];
			dataSize = data[index++];
			
			switch(dataId.u16) {
				case MTi1_XDI_PacketCounter: {
					if(dataSize == 2) {
						Tyu_2Byte packCnt;
						packCnt.byte[1] = data[index++];
						packCnt.byte[0] = data[index++];
						me->Data.PacketCounter = packCnt.u16;
					}
					break;
				}
				
				case MTi1_XDI_SampleTimeFine: {
					if(dataSize == 4) {
						Tyu_4Byte sampleTime;
						sampleTime.byte[3] = data[index++];
						sampleTime.byte[2] = data[index++];
						sampleTime.byte[1] = data[index++];
						sampleTime.byte[0] = data[index++];
						me->Data.SampleTimeFine = sampleTime.u32;
					}
					break;
				}
				
				case MTi1_XDI_SampleTimeCoarse: {
					if(dataSize == 4) {
						Tyu_4Byte sampleTime;
						sampleTime.byte[3] = data[index++];
						sampleTime.byte[2] = data[index++];
						sampleTime.byte[1] = data[index++];
						sampleTime.byte[0] = data[index++];
						me->Data.SampleTimeCoarse = sampleTime.u32;
					}
					break;
				}
				
				case MTi1_XDI_Quaternion: {
					if(dataSize == 16) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Quaternion.Q0 = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Quaternion.Q1 = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Quaternion.Q2 = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Quaternion.Q3 = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_RotationMatrix: {
					if(dataSize == 36) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.a = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.b = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.c = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.d = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.e = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.f = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.g = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.h = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RotationMatrix.i = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_EulerAngles: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Euler.Roll = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Euler.Pitch = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Euler.Yaw = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_DeltaV: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaV.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaV.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaV.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_Acceleration: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Acceleration.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Acceleration.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.Acceleration.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_FreeAcceleration: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.FreeAcceleration.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.FreeAcceleration.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.FreeAcceleration.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_AccelerationHR: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.AccelerationHR.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.AccelerationHR.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.AccelerationHR.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_RateOfTurn: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RateOfTurn.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RateOfTurn.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RateOfTurn.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_DeltaQ: {
					if(dataSize == 16) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaQ.Q0 = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaQ.Q1 = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaQ.Q2 = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.DeltaQ.Q3 = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_RateOfTurnHR: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RateOfTurnHR.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RateOfTurnHR.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.RateOfTurnHR.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_MagneticField: {
					if(dataSize == 12) {
						Tyu_4Byte tmp;
			
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.MagneticField.X = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.MagneticField.Y = tmp.f;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						me->Data.MagneticField.Z = tmp.f;
					}
					break;
				}
				
				case MTi1_XDI_StatusByte: {
					if(dataSize == 1) {
						
						me->Data.StatusByte = data[index++];
						if(me->statusByteCallback != NULL) {
							me->statusByteCallback(me->Data.StatusByte);
						}
					}
					break;
				}
				
				case MTi1_XDI_StatusWord: {
					if(dataSize == 4) {
						Tyu_4Byte tmp;
						
						tmp.byte[3] = data[index++];
						tmp.byte[2] = data[index++];
						tmp.byte[1] = data[index++];
						tmp.byte[0] = data[index++];
						
						memcpy(&me->Data.StatusWord, &tmp.u32, 4);
						if(me->statusWordCallback != NULL) {
							me->statusWordCallback(tmp.u32);
						}
					}
					break;
				}
				
				default:
					break;
			}
		}
	}
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

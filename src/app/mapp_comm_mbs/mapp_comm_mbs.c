/**
 ******************************************************************************
 * @file           : mapp_comm_mbs.c
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

/* Includes ------------------------------------------------------------------*/
#include "mapp_comm_mbs.h"

#include "resources\resources.h"

#include "faraabin.h"

#include "modbus_slave.h"

#include "i_driver\i_serial.h"

#include "hal\phal\port\stm32l4xx\inc\stm32l4xx_phal.h"
#include "bsp.h"

/* Private define ------------------------------------------------------------*/
#define MODBUS_UART					bsp.Com.Usb2serial

#define SERVER_ID						1
#define SERVER_LIVE_TIMEOUT	5000
#define SERVER_BAUDRATE			115200

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static bool init = false;

static uint8_t tx_buffer[300];

static uint16_t mm[11];

MODBUS_RTU_SLAVE_DEF_(mbs);

/* Private function prototypes -----------------------------------------------*/
static uint8_t AppInit(void);
static uint8_t AppStart(void* param);
static uint8_t AppRun(void);
static uint8_t AppTerminate(void);

static void Serial_EventNewFrame(object sender, void* e);
static uint8_t Serial_Send(uint8_t *data, uint16_t size);

static bool MemoryMap_RequestIsOk(sModbusSlaveRequestArgs *req);
static uint8_t MemoryMap_RequestHandle(sModbusSlaveRequestArgs *req);

/* Variables -----------------------------------------------------------------*/
sAppControlBlock MappCommMbs = {
  .Name = "MappCommMbs",
  .Init = AppInit,
  .Start = AppStart,
  .Run = AppRun,
  .Terminate = AppTerminate
};

/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                          ##### Exported Functions #####                          ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/


/*
╔══════════════════════════════════════════════════════════════════════════════════╗
║                            ##### Private Functions #####                         ║
╚══════════════════════════════════════════════════════════════════════════════════╝
*/
/**
* @brief 
* 
* @return uint8_t 
*/
uint8_t AppInit(void) {

  return 0;
}

/**
 * @brief 
 * 
 * @param param 
 * @return uint8_t 
 */
uint8_t AppStart(void* param) {
	
	init = false;
  
  MODBUS_UART->pReceiveBuffer = NULL;
  MODBUS_UART->ReceiveBufferSize = 300;
  MODBUS_UART->Baudrate = SERVER_BAUDRATE;
  MODBUS_UART->Parity = eSERIAL_PARITY_NONE;
  MODBUS_UART->StopBits = eSERIAL_STOP_BIT_1;
	MODBUS_UART->ReceiveTimeoutMs = 5000;
	if(fSerial_Open_(MODBUS_UART) != 0) {
    return 1;
  }
	
	fSerial_ReceiveNonBlock_(MODBUS_UART, MODBUS_UART->pReceiveBuffer, MODBUS_UART->ReceiveBufferSize);
  
	fSerial_RegisterIdleDetectedEvent_(MODBUS_UART, 20, Serial_EventNewFrame);
  //meSerial_Event_Error_(MODBUS_UART, Serial_EventError);
	//meSerial_Event_SendEnd_(MODBUS_UART, Serial_EventSendEnd);
  
  /*initialize mbs*/
	mbs.SlaveId = SERVER_ID;
	fModbusSlave_SetTxBufferStatically_(&mbs, tx_buffer, 300);
	mbs.pfSend = Serial_Send;
  
  mbs.pfMemoryMap_RequestIsOk = MemoryMap_RequestIsOk;
  mbs.pfMemoryMap_RequestHandle = MemoryMap_RequestHandle;
  
	fModbusSlave_Init(&mbs);
	
	mm[0] = 10;
	mm[1] = 11;
	mm[2] = 12;
  
  init = true; 

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppRun(void) {

  return 0;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppTerminate(void) {

  return 0;
}

/**
 * @brief 
 * 
 */
static void Serial_EventNewFrame(object sender, void* e) {
  
  if(init == false) {
    return;
  }
	
  fModbusSlave_HandleReceivedFrame(&mbs, MODBUS_UART->pReceiveBuffer, fSerial_ReceiveBuffer_Qty_(MODBUS_UART));
	
	fSerial_ReceiveNonBlock_(MODBUS_UART, MODBUS_UART->pReceiveBuffer, MODBUS_UART->ReceiveBufferSize);
}

/**
 * @brief 
 * 
 * @param data 
 * @param size 
 * @return uint8_t 
 */
static uint8_t Serial_Send(uint8_t *data, uint16_t size) {
  
  if(init == false) {
    return 1;//eME_RESULT_ERROR_INIT;
  }
  
	return fSerial_SendNonBlock_(MODBUS_UART, data, size);
}

/**
 * @brief 
 * 
 * @param req 
 * @return true 
 * @return false 
 */
static bool MemoryMap_RequestIsOk(sModbusSlaveRequestArgs *req) {
	
	return true;	
}

/**
 * @brief 
 * 
 * @param req 
 * @return uint8_t 
 */
static uint8_t MemoryMap_RequestHandle(sModbusSlaveRequestArgs *req) {
  
	uint8_t ret = 0;
  
  switch(req->AccessMode) {
		
    case eMB_MODE_READ: {
      
			uint16_t offset = 0;
      for(uint16_t i=0; i<req->Qty; i++) {
				
				fModbusTools_BitConverter_GetBytes_FromU16(mm[req->Addr + i], req->pData, offset);
				offset += 2;
      }
      
      break;
    }
    
    case eMB_MODE_WRITE: {
      
			uint16_t offset = 0;
      for(uint16_t i=0; i<req->Qty; i++) {
				
				mm[req->Addr + i] = fModbusTools_BitConverter_ToU16(req->pData, offset);
				offset += 2;
      }
			      
      break;
    }
		
    
    default: {
      return 1;
    }
  }
  
  return ret;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

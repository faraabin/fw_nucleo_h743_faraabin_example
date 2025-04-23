/**
******************************************************************************
* @file           : app_com_mbs.c
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
#include "app_com_mbs.h"

#include "modbus_slave.h"

#include "i_driver\i_serial.h"

#include "hal\phal\port\stm32l4xx\inc\stm32l4xx_phal.h"
#include "bsp.h"

#include "parameter_design\cg_Mbs_Hr_1_MbsHr.h"

/* Private define ------------------------------------------------------------*/
#define MODBUS_UART					bsp.Com.Usb2serial

#define SERVER_ID						1
#define SERVER_LIVE_TIMEOUT	5000
#define SERVER_BAUDRATE			115200

/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static bool init = false;

uint8_t tx_buffer[300];

uint16_t mm[11];

/* Private function prototypes -----------------------------------------------*/
static void Serial_EventNewFrame(object sender, void* e);
//static void Serial_EventError(void *handle, uint32_t error_code);
//static void Serial_EventSendEnd(void);
static uint8_t Serial_Send(uint8_t *data, uint16_t size);
//static void DictFunc(void *param);

static bool MemoryMap_RequestIsOk(sModbusSlaveRequestArgs *req);
static uint8_t MemoryMap_RequestHandle(sModbusSlaveRequestArgs *req);

/* Variables -----------------------------------------------------------------*/
MODBUS_RTU_SLAVE_DEF_(mbs);

/*
===============================================================================
                        ##### app_com_hmi_mbs.c Exported Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t AppCom_Mbs_Init(void) {
	
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

/*
===============================================================================
                    ##### app_com_hmi_mbs.c Private Functions #####
===============================================================================*/
/**
 * @brief 
 * 
 * @param param 
 */
//static void DictFunc(void *param) {
////  TysMbsMM_HMI_Obj_DictFunc();
////  meTRACE_DICT_VAR_EDITABLE_(TysMbsMM_HMI_Obj, mbs_mm_HMI, 1, NULL);
////  
////  meCONSOLE_ADD_GROUP_(prtl_mbs_mm, &(mbs_hmi.u_pdu.u_register_mm), "APP/COMM_MBS");
//}

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
 */
//static void Serial_EventSendEnd(void) {
//}

/**
 * @brief 
 * 
 * @param handle 
 * @param error_code 
 */
//static void Serial_EventError(void *handle, uint32_t error_code) {
//  
////  mePRINTF_TRACE_ERROR_("MODBUS_UART SERVER Error: %lu", error_code);
//  
//  meSerial_ReceiveNonBlock_(MODBUS_UART, MODBUS_UART->u_receive_buffer, MODBUS_UART->u_receive_buffer_size);
//}

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
	
	for(uint16_t i=0; i<req->Qty; i++) {
       
//		sMbs_HoldingRegister_Item *item = fMbs_FindItem(Mbs_Hr_1_MbsHr, MEMORY_MAP_QTY_(Mbs_Hr_1_MbsHr), req->Addr + i);
//		if(item == NULL) {
//			return false;
//		}
//		
//		switch(req->AccessMode) {
//			
//			case eMB_MODE_READ: {
//				
//				return !(item->Parameter->Type == ePARAMETER_TYPE_COMMAND);
//			}
//			
//			case eMB_MODE_WRITE: {
//				return (item->Parameter->Type == ePARAMETER_TYPE_COMMAND) | (item->Parameter->Type == ePARAMETER_TYPE_SETTING);
//			}
//		}
	}
  
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
       
//        sMbs_HoldingRegister_Item *item = fMbs_FindItem(Mbs_Hr_1_MbsHr, MEMORY_MAP_QTY_(Mbs_Hr_1_MbsHr), req->Addr + i);
//				if(item != NULL) {
//					
//					MEMORY_MAP_READ_U16_(item, &(req->pData[(2 * i)]));
//					
//				} else {
//					ret = 1;
//				}
      }
      
      break;
    }
    
    case eMB_MODE_WRITE: {
      
			uint16_t offset = 0;
      for(uint16_t i=0; i<req->Qty; i++) {
				
				mm[req->Addr + i] = fModbusTools_BitConverter_ToU16(req->pData, offset);
				offset += 2;
				
				
//				sMbs_HoldingRegister_Item *item = fMbs_FindItem(Mbs_Hr_1_MbsHr, MEMORY_MAP_QTY_(Mbs_Hr_1_MbsHr), req->Addr + i);
//				if(item != NULL) {
//					
//					MEMORY_MAP_WRITE_U16_(item, &(req->pData[(2 * i)]));
//					
//				} else {
//					ret = 1;
//				}				
      }
			
			ret = 0;
			for(uint16_t i=0; i<req->Qty; i++) {
				
//				sMbs_HoldingRegister_Item *item = fMbs_FindItem(Mbs_Hr_1_MbsHr, MEMORY_MAP_QTY_(Mbs_Hr_1_MbsHr), req->Addr + i);
//				if(item != NULL) {
//					
//					if(fSmartData_Refresh(item->Parameter->Data) != 0) {
//						ret = 1;
//					}
//				}				
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

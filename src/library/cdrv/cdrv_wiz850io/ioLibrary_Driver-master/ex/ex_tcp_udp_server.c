/**
 ******************************************************************************
 *  @file         ex_tcp_udp_server.c
 *  @brief        ...
 *  @author       ...
 *  @version      0.0.0.1
 *  @date         yyyy/mm/dd
 *  @copyright    COPYRIGHT(c) 2018 MicroEmbeds
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 * DESCRIPTION:
 *
 ******************************************************************************
 * HOW TO USE:
 *
 ******************************************************************************
 @verbatim
 @endverbatim
*/

/* Includes ------------------------------------------------------------------*/
#include "ex_tcp_udp_server.h"

#include "..\Ethernet\socket.h"

#include "faraabin.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
extern uint16_t sock_is_sending;

/*
===============================================================================
                       ##### Exported Function #####
===============================================================================*/
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
void ex_tcp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, void(*receive_frame)(uint8_t *data, uint16_t size), bool debug) {
  uint8_t ret;
  uint16_t size = 0;
  uint8_t destip[4];
  uint16_t destport;

  switch(getSn_SR(sn)) {
    
    case SOCK_ESTABLISHED: {
      if(getSn_IR(sn) & Sn_IR_CON) {
          
        getSn_DIPR(sn, destip);
        destport = getSn_DPORT(sn);
        
        if(debug == true) {
          FARAABIN_Printf_("%d:Connected - %d.%d.%d.%d : %d",sn, destip[0], destip[1], destip[2], destip[3], destport);
        }
        setSn_IR(sn,Sn_IR_CON);
      }
		 
      if((size = getSn_RX_RSR(sn)) > 0) {
        if(size > buff_size) {
          size = buff_size;
        }
        ret = recv(sn, buffer, size);

        if(ret >0) {
          if(receive_frame != NULL) {
            receive_frame(buffer, size);
          }
        }
      }
      break;
    }
    
    case SOCK_CLOSE_WAIT: {
      ret = disconnect(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          FARAABIN_Printf_("%d:Socket Closed", sn);
        } else { 
          FARAABIN_PrintfError_("%d:Socket Close ERROR", sn);
        }
      }
      break;
    }
      
    case SOCK_INIT: {
      ret = listen(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          FARAABIN_PrintfError_("%d:Listen, TCP server, port [%d] ERROR", sn, port);
        } else {
          FARAABIN_Printf_("%d:Listen, TCP server, port [%d]", sn, port);
        }
      }
      break;
    }
    
    case SOCK_CLOSED: {
      ret = socket(sn, Sn_MR_TCP, port, SF_IO_NONBLOCK);
      if(debug == true) {
        if(ret != sn) {
          FARAABIN_PrintfError_("%d:Create socket ERROR", sn);
        }
      }
      break;
    }

    default: {
      break;
    }
  }
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
void ex_udp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, void(*receive_frame)(uint8_t *data, uint16_t size, uint8_t *addr, uint16_t port), bool debug) {
  uint8_t ret;
  uint16_t size = 0;
  uint8_t destip[4];
  uint16_t destport;

  switch(getSn_SR(sn)) {
    
    case SOCK_ESTABLISHED: {
      if(getSn_IR(sn) & Sn_IR_CON) {
          
        getSn_DIPR(sn, destip);
        destport = getSn_DPORT(sn);
        
        if(debug == true) {
          FARAABIN_Printf_("%d:Connected - %d.%d.%d.%d : %d",sn, destip[0], destip[1], destip[2], destip[3], destport);
        }
        setSn_IR(sn,Sn_IR_CON);
      }
		 
      if((size = getSn_RX_RSR(sn)) > 0) {
        if(size > buff_size) {
          size = buff_size;
        }
				uint8_t addr[40];
				uint16_t port;
        ret = recvfrom(sn, buffer, size, addr, &port);

        if(ret >0) {
          if(receive_frame != NULL) {
            receive_frame(buffer, ret, addr, port);
          }
        }
      }
      break;
    }
    
    case SOCK_CLOSE_WAIT: {
      ret = disconnect(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          FARAABIN_Printf_("%d:Socket Closed", sn);
        } else { 
          FARAABIN_PrintfError_("%d:Socket Close ERROR", sn);
        }
      }
      break;
    }
      
    case SOCK_INIT: {
      ret = listen(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          FARAABIN_PrintfError_("%d:Listen, TCP server, port [%d] ERROR", sn, port);
        } else {
          FARAABIN_Printf_("%d:Listen, TCP server, port [%d]", sn, port);
        }
      }
      break;
    }
    
    case SOCK_CLOSED: {
      ret = socket(sn, Sn_MR_UDP, port, SF_IO_NONBLOCK);
      if(debug == true) {
        if(ret != sn) {
          FARAABIN_PrintfError_("%d:Create socket ERROR", sn);
        }
      }
      break;
    }
		
		case SOCK_UDP: {
      if((size = getSn_RX_RSR(sn)) > 0) {
        if(size > buff_size) {
          size = buff_size;
        }
				uint8_t addr[40];
				uint16_t port;
        ret = recvfrom(sn, buffer, size, addr, &port);

        if(ret >0) {
          if(receive_frame != NULL) {
            receive_frame(buffer, ret, addr, port);
          }
        }
      }
      break;
    }

    default: {
      break;
    }
  }
}

/**
  * @brief
  * @note  
  * @param  
  * @retval
*/
bool ex_socket_is_sending(uint8_t sn) {
  uint8_t tmp;
  
  if(sock_is_sending & (1<<sn)) {
    tmp = getSn_IR(sn);
    if(tmp & Sn_IR_SENDOK) {
      setSn_IR(sn, Sn_IR_SENDOK);
      sock_is_sending &= ~(1<<sn);
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

/*
===============================================================================
                       ##### Private Functios #####
===============================================================================*/
/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

/**
 ******************************************************************************
 *  @file         ex_tcp_server.c
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
#include "ex_tcp_server.h"

#include "..\Ethernet\wizchip_conf.h"
#include "..\Ethernet\socket.h"

#include "library\faraabin\faraabin.h"

/** @addtogroup Group_Name
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint16_t any_port = 	50000;
static uint8_t curr_state[8] = {0,};
static uint8_t sock_state[8] = {0,};
static char* msg_v4 = "IPv4 mode";
static char* msg_v6 = "IPv6 mode";
static char* msg_dual = "Dual IP mode";

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
void ex_tcp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, uint8_t mode, void(*receive_frame)(uint8_t *data, uint16_t size), void(*event_cb)(TyeSocketEvent event_id), bool debug) {
	uint8_t ret;
  uint16_t size = 0;
  uint8_t destip[4];
  uint16_t destport;
	
	uint16_t tmp_status = getSn_SR(sn);
  switch(tmp_status) {
    
    case SOCK_ESTABLISHED: {
      if(getSn_IR(sn) & Sn_IR_CON) {
          
        getSn_DIPR(sn, destip);
        destport = getSn_DPORTR(sn);
        
        if(debug == true) {
          mePRINTF_TRACE_("%d:Connected - %d.%d.%d.%d : %d",sn, destip[0], destip[1], destip[2], destip[3], destport);
        }
        if(event_cb != NULL) {
          event_cb(eSOCKET_EVENT_CONNECT);
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
          mePRINTF_TRACE_("%d:Socket Closed", sn);
        } else { 
          mePRINTF_TRACE_ERROR_("%d:Socket Close ERROR", sn);
        }
      }
      if(event_cb != NULL) {
        event_cb(eSOCKET_EVENT_DISCONNECT);
      }
      break;
    }
      
    case SOCK_INIT: {
      ret = listen(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          mePRINTF_TRACE_ERROR_("%d:Listen, TCP server, port [%d] ERROR", sn, port);
        } else {
          mePRINTF_TRACE_("%d:Listen, TCP server, port [%d]", sn, port);
        }
      }  
      if(event_cb != NULL) {
        event_cb(eSOCKET_EVENT_LISTEN);
      }      
      break;
    }
    
    case SOCK_CLOSED: {
			switch(mode) {
				case AS_IPV4:
				ret = socket(sn, Sn_MR_TCP4, port, SOCK_IO_NONBLOCK);
				break;
		case AS_IPV6:
				ret = socket(sn, Sn_MR_TCP6, port, SOCK_IO_NONBLOCK);
				break;
		case AS_IPDUAL:
				ret = socket(sn, Sn_MR_TCPD, port, SOCK_IO_NONBLOCK);
				break;
			}
//      ret = socket(sn, Sn_MR_TCP, port, SF_IO_NONBLOCK);
      if(debug == true) {
        if(ret != sn) {
          mePRINTF_TRACE_ERROR_("%d:Create socket ERROR", sn);
        }
      }
      
      if(event_cb != NULL) {
        event_cb(eSOCKET_EVENT_DISCONNECT);
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
void ex_udp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, uint8_t mode, void(*receive_frame)(uint8_t *data, uint16_t size, uint8_t *addr, uint16_t port, uint8_t addr_len), bool debug) {
	uint8_t ret;
  uint16_t size = 0;
  uint8_t destip[4];
  uint16_t destport;
	uint8_t addr_len;

  switch(getSn_SR(sn)) {
    
    case SOCK_ESTABLISHED: {
      if(getSn_IR(sn) & Sn_IR_CON) {
          
        getSn_DIPR(sn, destip);
        destport = getSn_DPORTR(sn);
        
        if(debug == true) {
          mePRINTF_TRACE_("%d:Connected - %d.%d.%d.%d : %d",sn, destip[0], destip[1], destip[2], destip[3], destport);
        }
        setSn_IR(sn,Sn_IR_CON);
      }
		 
      if((size = getSn_RX_RSR(sn)) > 0) {
        if(size > buff_size) {
          size = buff_size;
        }
				uint8_t addr[40];
				uint16_t port;
        ret = recvfrom(sn, buffer, size, addr, &port, &addr_len);

        if(ret >0) {
          if(receive_frame != NULL) {
            receive_frame(buffer, ret, addr, port, addr_len);
          }
        }
      }
      break;
    }
    
    case SOCK_CLOSE_WAIT: {
      ret = disconnect(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          mePRINTF_TRACE_("%d:Socket Closed", sn);
        } else { 
          mePRINTF_TRACE_ERROR_("%d:Socket Close ERROR", sn);
        }
      }
      break;
    }
      
    case SOCK_INIT: {
      ret = listen(sn);
      if(debug == true) {
        if(ret != SOCK_OK) {
          mePRINTF_TRACE_ERROR_("%d:Listen, TCP server, port [%d] ERROR", sn, port);
        } else {
          mePRINTF_TRACE_("%d:Listen, TCP server, port [%d]", sn, port);
        }
      }
      break;
    }
    
    case SOCK_CLOSED: {
      switch(mode) {
				case AS_IPV4:
				ret = socket(sn, Sn_MR_UDP4, port, SOCK_IO_NONBLOCK);
				break;
		case AS_IPV6:
				ret = socket(sn, Sn_MR_UDP6, port, SOCK_IO_NONBLOCK);
				break;
		case AS_IPDUAL:
				ret = socket(sn, Sn_MR_UDPD, port, SOCK_IO_NONBLOCK);
				break;
			}
      if(debug == true) {
        if(ret != sn) {
          mePRINTF_TRACE_ERROR_("%d:Create socket ERROR", sn);
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
        ret = recvfrom(sn, buffer, size, addr, &port, &addr_len);

        if(ret >0) {
          if(receive_frame != NULL) {
            receive_frame(buffer, ret, addr, port, addr_len);
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
/**
  * @brief
  * @note  
  * @param  
  * @retval
*/

/**End of Group_Name
  * @}
  */

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

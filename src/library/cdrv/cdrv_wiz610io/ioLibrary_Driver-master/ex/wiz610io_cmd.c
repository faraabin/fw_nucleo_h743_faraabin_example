/**
******************************************************************************
* @file           : wiz610io_cmd.c
* @brief          :
* @note           :
* @copyright      : COPYRIGHT© 2022 FaraabinCo
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright© 2022 FaraabinCo.
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
#include "wiz610io_cmd.h"

#include "..\Ethernet\socket.h"
#include "ex_tcp_server.h"

/* Private typedef -----------------------------------------------------------*/
meCONSOLE_OBJ_(void);

/* Private define ------------------------------------------------------------*/
#define BUFF_SIZE 100

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int loopback_sn, loopback_port;
static uint8_t loopback_buffer[BUFF_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void receive_frame_tcp(uint8_t *data, uint16_t size) {
  send(loopback_sn, data, size);
}

static void event_cb_tcp(TyeSocketEvent event) {
  
  switch(event) {
    
    case eSOCKET_EVENT_CONNECT: {
      mePRINTF_TRACE_("\r\neSOCKET_EVENT_CONNECT");
      break;
    }
    
    case eSOCKET_EVENT_DISCONNECT: {
      mePRINTF_TRACE_("\r\neSOCKET_EVENT_DISCONNECT");
      break;
    }
    
    case eSOCKET_EVENT_INIT: {
      mePRINTF_TRACE_("\r\neSOCKET_EVENT_INIT");
      break;
    }
    
    case eSOCKET_EVENT_LISTEN: {
      mePRINTF_TRACE_("\r\neSOCKET_EVENT_LISTEN");
      break;
    }
  }
}

static void receive_frame_udp(uint8_t *data, uint16_t size, uint8_t *addr, uint16_t port, uint8_t addr_len) {
	mePRINTF_TRACE_("%s", data);
  sendto(loopback_sn, data, size, addr, port, addr_len);
}

/* Variables -----------------------------------------------------------------*/

/*
===============================================================================
                    ##### wiz610io_cmd.c Private Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, IPV4_NETINFO,
"type cmd help here") {
  
  wiz_NetInfo net_info;
  wizchip_getnetinfo(&net_info);
  
  mePRINTF_("\n\nW6100 Ethernet adapter:\n");
  mePRINTF_("\n  Physical Address.....: %x-%x-%x-%x-%x-%x", net_info.mac[0], net_info.mac[1], net_info.mac[2], net_info.mac[3], net_info.mac[4], net_info.mac[5]);
  mePRINTF_("\n  IPV4 Address.........: %u.%u.%u.%u", net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3]);
  mePRINTF_("\n  IPV4 Subnet Mask.....: %u.%u.%u.%u", net_info.sn[0], net_info.sn[1], net_info.sn[2], net_info.sn[3]);
	mePRINTF_("\n  DNS Server...........: %u.%u.%u.%u", net_info.dns[0], net_info.dns[1], net_info.dns[2], net_info.dns[3]);
  mePRINTF_("\n  IPV4 Default Gateway.: %u.%u.%u.%u", net_info.gw[0], net_info.gw[1], net_info.gw[2], net_info.gw[3]);
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, IPV6_NETINFO,
"type cmd help here") {
  
	uint8_t ga6r_info[16];
	uint8_t llar_info[16];
	uint8_t guar_info[16];
	uint8_t sub6r_info[16];
  
	getGA6R(ga6r_info);
	getLLAR(llar_info);
	getGUAR(guar_info);
	getSUB6R(sub6r_info);

	mePRINTF_("\n  IPV6 Default Gateway.......: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
					 ((uint16_t)ga6r_info[0] << 8) | ((uint16_t)ga6r_info[1]), ((uint16_t)ga6r_info[2] << 8) | ((uint16_t)ga6r_info[3]),
					 ((uint16_t)ga6r_info[4] << 8) | ((uint16_t)ga6r_info[5]), ((uint16_t)ga6r_info[6] << 8) | ((uint16_t)ga6r_info[7]),
					 ((uint16_t)ga6r_info[8] << 8) | ((uint16_t)ga6r_info[9]), ((uint16_t)ga6r_info[10] << 8) | ((uint16_t)ga6r_info[11]),
					 ((uint16_t)ga6r_info[12] << 8) | ((uint16_t)ga6r_info[13]), ((uint16_t)ga6r_info[14] << 8) | ((uint16_t)ga6r_info[15]));
	mePRINTF_("\n  IPV6 Link Local Address....: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
					 ((uint16_t)llar_info[0] << 8) | ((uint16_t)llar_info[1]), ((uint16_t)llar_info[2] << 8) | ((uint16_t)llar_info[3]),
					 ((uint16_t)llar_info[4] << 8) | ((uint16_t)llar_info[5]), ((uint16_t)llar_info[6] << 8) | ((uint16_t)llar_info[7]),
					 ((uint16_t)llar_info[8] << 8) | ((uint16_t)llar_info[9]), ((uint16_t)llar_info[10] << 8) | ((uint16_t)llar_info[11]),
					 ((uint16_t)llar_info[12] << 8) | ((uint16_t)llar_info[13]), ((uint16_t)llar_info[14] << 8) | ((uint16_t)llar_info[15]));
	mePRINTF_("\n  IPV6 Global Unicast Address: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
					 ((uint16_t)guar_info[0] << 8) | ((uint16_t)guar_info[1]), ((uint16_t)guar_info[2] << 8) | ((uint16_t)guar_info[3]),
					 ((uint16_t)guar_info[4] << 8) | ((uint16_t)guar_info[5]), ((uint16_t)guar_info[6] << 8) | ((uint16_t)guar_info[7]),
					 ((uint16_t)guar_info[8] << 8) | ((uint16_t)guar_info[9]), ((uint16_t)guar_info[10] << 8) | ((uint16_t)guar_info[11]),
					 ((uint16_t)guar_info[12] << 8) | ((uint16_t)guar_info[13]), ((uint16_t)guar_info[14] << 8) | ((uint16_t)guar_info[15]));
	mePRINTF_("\n  IPV6 Prefix................: %04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
					 ((uint16_t)sub6r_info[0] << 8) | ((uint16_t)sub6r_info[1]), ((uint16_t)sub6r_info[2] << 8) | ((uint16_t)sub6r_info[3]),
					 ((uint16_t)sub6r_info[4] << 8) | ((uint16_t)sub6r_info[5]), ((uint16_t)sub6r_info[6] << 8) | ((uint16_t)sub6r_info[7]),
					 ((uint16_t)sub6r_info[8] << 8) | ((uint16_t)sub6r_info[9]), ((uint16_t)sub6r_info[10] << 8) | ((uint16_t)sub6r_info[11]));
	
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, LOOPBACK_TEST_TCP_IPV4,
"type cmd help here") {
  
  meCONSOLE_GET_PAR_(2, "%u %u", &loopback_sn, &loopback_port);
  
  meCONSOLE_LOOP_(2) {
    ex_tcp_server(loopback_sn, loopback_port, loopback_buffer, 100, AS_IPV4, receive_frame_tcp, event_cb_tcp, true);
    meCONSOLE_LOOP_END_;
  }    
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, LOOPBACK_TEST_TCP_IPV6,
"type cmd help here") {
  
  meCONSOLE_GET_PAR_(2, "%u %u", &loopback_sn, &loopback_port);
  
  meCONSOLE_LOOP_(10) {
    ex_tcp_server(loopback_sn, loopback_port, loopback_buffer, BUFF_SIZE, AS_IPV6, receive_frame_tcp, event_cb_tcp, true);
    meCONSOLE_LOOP_END_;
  }
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, LOOPBACK_TEST_TCP_IPDUAL,
"type cmd help here") {
  
  meCONSOLE_GET_PAR_(2, "%u %u", &loopback_sn, &loopback_port);
  
  meCONSOLE_LOOP_(100) {
    ex_tcp_server(loopback_sn, loopback_port, loopback_buffer, 100, AS_IPDUAL, receive_frame_tcp, event_cb_tcp, true);
    meCONSOLE_LOOP_END_;
  }    
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, LOOPBACK_TEST_UDP_IPV4,
"type cmd help here") {
  
  meCONSOLE_GET_PAR_(2, "%u %u", &loopback_sn, &loopback_port);
  
  meCONSOLE_LOOP_(100) {
    ex_udp_server(loopback_sn, loopback_port, loopback_buffer, 100, AS_IPV4, receive_frame_udp, true);
    meCONSOLE_LOOP_END_;
  }    
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, LOOPBACK_TEST_UDP_IPV6,
"type cmd help here") {
  
  meCONSOLE_GET_PAR_(2, "%u %u", &loopback_sn, &loopback_port);
  
  meCONSOLE_LOOP_(100) {
    ex_udp_server(loopback_sn, loopback_port, loopback_buffer, 100, AS_IPV6, receive_frame_udp, true);
    meCONSOLE_LOOP_END_;
  }    
  
	meCONSOLE_END_;
}

/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_CMD_(wiz610io, LOOPBACK_TEST_UDP_IPDUAL,
"type cmd help here") {
  
  meCONSOLE_GET_PAR_(2, "%u %u", &loopback_sn, &loopback_port);
  
  meCONSOLE_LOOP_(100) {
    ex_udp_server(loopback_sn, loopback_port, loopback_buffer, 100, AS_IPDUAL, receive_frame_udp, true);
    meCONSOLE_LOOP_END_;
  }    
  
	meCONSOLE_END_;
}

/*
===============================================================================
                        ##### wiz610io_cmd.c Functions #####
===============================================================================*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
/**
  * @brief
  * @note
  * @param
  * @retval
*/
meCONSOLE_GROUP_(wiz610io,
"type cmd help here") {
  meCONSOLE_ADD_CMD_(wiz610io, IPV4_NETINFO, 0);
	meCONSOLE_ADD_CMD_(wiz610io, IPV6_NETINFO, 0);
	meCONSOLE_ADD_CMD_(wiz610io, LOOPBACK_TEST_TCP_IPV4, 0);
	meCONSOLE_ADD_CMD_(wiz610io, LOOPBACK_TEST_TCP_IPV6, 0);
	meCONSOLE_ADD_CMD_(wiz610io, LOOPBACK_TEST_TCP_IPDUAL, 0);
	meCONSOLE_ADD_CMD_(wiz610io, LOOPBACK_TEST_UDP_IPV4, 0);
	meCONSOLE_ADD_CMD_(wiz610io, LOOPBACK_TEST_UDP_IPV6, 0);
	meCONSOLE_ADD_CMD_(wiz610io, LOOPBACK_TEST_UDP_IPDUAL, 0);
  meCONSOLE_END_;
}

/************************ © COPYRIGHT FaraabinCo *****END OF FILE****/

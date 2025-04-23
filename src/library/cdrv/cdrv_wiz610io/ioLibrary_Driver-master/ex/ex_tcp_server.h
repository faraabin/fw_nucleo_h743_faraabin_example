/**
 ******************************************************************************
 *  @file         ex_tcp_server.h
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
 @verbatim
 @endverbatim
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ex_tcp_server_H
#define __ex_tcp_server_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include "library\type\me_type.h"

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
typedef enum {
  
  eSOCKET_EVENT_CONNECT,
  eSOCKET_EVENT_DISCONNECT,
  eSOCKET_EVENT_INIT,
  eSOCKET_EVENT_LISTEN,
  
}TyeSocketEvent;

/* Exported macro ------------------------------------------------------------*/
#define SOCK_TCP4	(Sn_MR_TCP)
#define SOCK_TCP6	(Sn_MR_TCP6)
#define SOCK_TCPD	(Sn_MR_TCPD)

#define SOCK_UDP4	(Sn_MR_UDP4)
#define SOCK_UDP6	(Sn_MR_UDP6)
#define SOCK_UDPD	(Sn_MR_UDPD)

#define AS_IPV4		2
#define AS_IPV6		23
#define AS_IPDUAL	11

/* Exported functions --------------------------------------------------------*/
/* Extern functions ----------------------------------------------------------*/
void ex_tcp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, uint8_t mode, void(*receive_frame)(uint8_t *data, uint16_t size), void(*event_cb)(TyeSocketEvent event_id), bool debug);
void ex_udp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, uint8_t mode, void(*receive_frame)(uint8_t *data, uint16_t size, uint8_t *addr, uint16_t port, uint8_t addr_len), bool debug);

bool ex_socket_is_sending(uint8_t sn);
  
/* Extern Object or Variable -------------------------------------------------*/

/**End of Group_Name
  * @}
  */

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/************************ (C) COPYRIGHT MicroEmbeds **********END OF FILE******/

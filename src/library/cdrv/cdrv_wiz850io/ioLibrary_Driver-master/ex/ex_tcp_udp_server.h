/**
 ******************************************************************************
 *  @file         ex_tcp_udp_server.h
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
#ifndef __ex_tcp_udp_server_H
#define __ex_tcp_udp_server_H

#ifdef __cplusplus
extern "C"{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/** @addtogroup Group_Name
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types (enum, struct, union,...)-----------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Extern functions ----------------------------------------------------------*/
void ex_tcp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, void(*receive_frame)(uint8_t *data, uint16_t size), bool debug);
void ex_udp_server(uint8_t sn, uint16_t port, uint8_t *buffer, uint16_t buff_size, void(*receive_frame)(uint8_t *data, uint16_t size, uint8_t *addr, uint16_t port), bool debug);
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

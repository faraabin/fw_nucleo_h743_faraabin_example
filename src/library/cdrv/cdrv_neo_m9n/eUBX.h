#ifndef _EUBX_H
#define _EUBX_H

#include <stdint.h>

/* ID/CLASS Code*/
#define UBX_ACK_ACK 0x0501
#define UBX_ACK_NAK 0x0500

#define UBX_CFG_PRT 0x0600
#define UBX_NAV_PVT 0x0107
#define UBX_CFG_MSG 0x0601
#define UBX_CFG_RATE 0x0608


#define UBX_UART_PRTID 0x01


/* HEADERS */
#define UBX_HEADER_1  0xB5
#define UBX_HEADER_2  0x62
/* Port Configuration Settings*/
#define UBX_UART_TX_READY_EN          0x0001
#define UBX_UART_TX_READY_DIS         0x0000
#define UBX_UART_TX_READY_HIGH_ACTIVE 0x0002
#define UBX_UART_TX_READY_LOW_ACTIVE  0x0000
#define UBX_UART_TX_READY_PIN         0x0000
#define UBX_UART_TX_READY_THRESHOLD   0x0000  

#define UBX_UART_MODE_5BIT 0b0000000000000000
#define UBX_UART_MODE_6BIT 0b0000000001000000
#define UBX_UART_MODE_7BIT 0b0000000010000000
#define UBX_UART_MODE_8BIT 0b0000000011000000

#define UBX_UART_MODE_EVEN_PARITY 0b0000000000000000
#define UBX_UART_MODE_ODD_PARITY  0b0000001000000000
#define UBX_UART_MODE_NO_PARITY   0b0000100000000000

#define UBX_UART_MODE_1_STOPBIT   0b0000000000000000
#define UBX_UART_MODE_1_5_STOPBIT 0b0001000000000000
#define UBX_UART_MODE_2_STOPBIT   0b0010000000000000
#define UBX_UART_MODE_0_5_STOPBIT 0b0011000000000000

#define UBX_UART_IN_PROTOCOL_UBX   0b0000000000000001
#define UBX_UART_IN_PROTOCOL_NMEA  0b0000000000000010
#define UBX_UART_IN_PROTOCOL_RTCM  0b0000000000000100
#define UBX_UART_IN_PROTOCOL_RTCM3 0b0000000000100000

#define UBX_UART_OUT_PROTOCOL_UBX   0b0000000000000001
#define UBX_UART_OUT_PROTOCOL_NMEA  0b0000000000000010
#define UBX_UART_OUT_PROTOCOL_RTCM3 0b0000000001000000

#define UBX_UART_FLAG_ACTIVE   0b0000000000000010
#define UBX_UART_FLAG_DEACTIVE 0b0000000000000000

typedef struct {
    uint16_t msg_class_id;
    uint8_t* payload;
    uint16_t payload_len;
}eUBX_MsgTypedef;

typedef struct {
    uint8_t port_id;
    uint16_t buadrate;

}eUBX_PrtCfgTypedef;

uint16_t eUBX_PacketGenerator(uint8_t* buffer, eUBX_MsgTypedef* msg);
uint8_t eUBX_PacketParser(uint8_t* buffer, eUBX_MsgTypedef* msg);
uint16_t eUBX_PortConfig(uint8_t* buffer, uint8_t port_id,
                                         uint32_t buadrate,
                                         uint16_t tx_ready,
                                         uint32_t mode,
                                         uint16_t in_protocol,
                                         uint16_t out_protocol,
                                         uint16_t flag);


uint16_t eUBX_MessageRequest(uint8_t* buffer, uint16_t class_id);
uint16_t eUBX_ConfigMessage(uint8_t* buffer, uint16_t class_id);
uint16_t eUBX_MsgRateConfig(uint8_t* buffer, uint16_t meas_rate,uint16_t nav_rate, uint16_t time_ref);
#endif /*_EUBX_H*/

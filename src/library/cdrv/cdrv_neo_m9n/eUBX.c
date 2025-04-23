#include <stdio.h>
#include "eUBX.h"

void UBX_ChecksumCal(uint8_t *packet,uint16_t start, 
                     uint16_t stop, uint8_t *CK_A,uint8_t *CK_B);


uint16_t eUBX_PacketGenerator(uint8_t* buffer, eUBX_MsgTypedef* msg) {

    buffer[0] = UBX_HEADER_1;
    buffer[1] = UBX_HEADER_2;
    buffer[2] = (uint8_t)(msg->msg_class_id >>8);
    buffer[3] = (uint8_t)(msg->msg_class_id);
    buffer[4] = (uint8_t)(msg->payload_len);
    buffer[5] = (uint8_t)(msg->payload_len>>8);
    for(uint16_t i=0; i<msg->payload_len; i++) {
        buffer[i+6] = msg->payload[i]; 
    }
    UBX_ChecksumCal(buffer,2,msg->payload_len+6,
                    &buffer[msg->payload_len+6],
                    &buffer[msg->payload_len+7]);
    return(msg->payload_len+8);
}

uint8_t eUBX_PacketParser(uint8_t* buffer, eUBX_MsgTypedef* msg) {
    uint8_t test_ck_a = 0;
    uint8_t test_ck_b = 0; 
    uint16_t tmp_len = ((uint16_t)buffer[5] << 8)|buffer[4];
  

    UBX_ChecksumCal(buffer,2,tmp_len+6,&test_ck_a,&test_ck_b);

    if(buffer[0] == UBX_HEADER_1 && buffer[1] == UBX_HEADER_2 &&
        buffer[tmp_len+6] == test_ck_a && buffer[tmp_len+7] == test_ck_b) {

        uint16_t tmp_class_id = ((uint16_t)(buffer[2]<<8))|buffer[3];
        uint16_t tmp_len = ((uint16_t)(buffer[5]<<8))|buffer[4];
        for(uint16_t i=0; i<tmp_len; i++) {
            msg->payload[i] = buffer[i+6]; 
        }
        msg->msg_class_id= tmp_class_id;
        msg->payload_len = tmp_len;

        return 1;
    }
    return 0;
}
uint16_t eUBX_PortConfig(uint8_t* buffer, uint8_t port_id,
                                         uint32_t buadrate,
                                         uint16_t tx_ready,
                                         uint32_t mode,
                                         uint16_t in_protocol,
                                         uint16_t out_protocol,
                                         uint16_t flag)
{
   //uint8_t tmp_payload[19];
		uint8_t tmp_payload[20];
		eUBX_MsgTypedef tmp = {.msg_class_id = UBX_CFG_PRT,
                         .payload_len = 20,
                         .payload = tmp_payload};
    tmp_payload[0] = port_id;
    tmp_payload[1] = 0x00;
    tmp_payload[2] = (uint8_t)(tx_ready);
    tmp_payload[3] = (uint8_t)(tx_ready>>8);
    tmp_payload[4] = (uint8_t)(mode);
    tmp_payload[5] = (uint8_t)(mode>>8);
    tmp_payload[6] = (uint8_t)(mode>>16);
    tmp_payload[7] = (uint8_t)(mode>>24);
    tmp_payload[8] = (uint8_t)(buadrate);
    tmp_payload[9] = (uint8_t)(buadrate>>8);
    tmp_payload[10]= (uint8_t)(buadrate>>16);
    tmp_payload[11]= (uint8_t)(buadrate>>24);
    tmp_payload[12]= (uint8_t)(in_protocol);
    tmp_payload[13]= (uint8_t)(in_protocol>>8);
    tmp_payload[14]= (uint8_t)(out_protocol);
    tmp_payload[15]= (uint8_t)(out_protocol>>8);
    tmp_payload[16]= (uint8_t)(flag);
    tmp_payload[17]= (uint8_t)(flag>>8);
    tmp_payload[18]= 0x00;
    tmp_payload[19]= 0x00;
    return eUBX_PacketGenerator(buffer,&tmp);        
}
uint16_t eUBX_ConfigMessage(uint8_t* buffer, uint16_t class_id) {
	   uint8_t tmp_payload[3];
	   eUBX_MsgTypedef tmp = {.msg_class_id = UBX_CFG_MSG,
	                         .payload_len = 3,
	                         .payload = tmp_payload};
	   tmp_payload[0] = (uint8_t)(0x01);
	   tmp_payload[1] = (uint8_t)(0x07);
	   tmp_payload[2] = 1;
	   return eUBX_PacketGenerator(buffer,&tmp);
}
uint16_t eUBX_MessageRequest(uint8_t* buffer, uint16_t class_id) {
	   uint8_t tmp_payload = 0x00;
	   eUBX_MsgTypedef tmp = {.msg_class_id = class_id,
	                         .payload_len = 0,
	                         .payload = &tmp_payload};
	   return eUBX_PacketGenerator(buffer,&tmp);
}
uint16_t eUBX_MsgRateConfig(uint8_t* buffer, uint16_t meas_rate,uint16_t nav_rate, uint16_t time_ref)
{
	   uint8_t tmp_payload[6];
	   eUBX_MsgTypedef tmp = {.msg_class_id = UBX_CFG_RATE,
	                         .payload_len = 6,
	                         .payload = tmp_payload};
	   tmp_payload[0] = (uint8_t)(meas_rate);
	   tmp_payload[1] = (uint8_t)(meas_rate>>8);
	   tmp_payload[2] = (uint8_t)(nav_rate);
	   tmp_payload[3] = (uint8_t)(nav_rate>>8);
	   tmp_payload[4] = (uint8_t)(time_ref);
	   tmp_payload[5] = (uint8_t)(time_ref>>8);
	   return eUBX_PacketGenerator(buffer,&tmp);
}
void UBX_ChecksumCal(uint8_t *packet,uint16_t start, 
                     uint16_t stop, uint8_t *CK_A,uint8_t *CK_B)
{
    (*CK_A) = 0;
    (*CK_B) = 0;
    for(uint16_t i=start; i<stop; i++) {
        (*CK_A) = (*CK_A) + packet[i];
        (*CK_B) = (*CK_B) + (*CK_A);
    }
}

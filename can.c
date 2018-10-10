#include "can.h"
#include "MCP2515.h"
#include <stdio.h>

void CAN_init(void){

    MCP_bit_modify(MCP_RXB0CTRL, 0b01100000, 0xFF);
    MCP_send_single_data_byte(MCP_CANCTRL, MODE_LOOPBACK);

}

void CAN_send(Can_block* can_block){
    //MCP_bit_modify(MCP_TXB0CTRL, 0b00000111, 0x07);
    MCP_send_single_data_byte(MCP_SID0_HIGH, can_block -> id >> 3);
    MCP_send_single_data_byte(MCP_SID0_LOW, can_block -> id << 5);
    MCP_send_single_data_byte(MCP_RXB0DLC, (can_block -> length) & (0x0F) ); //Set data length

    for(int i = 0; i < can_block -> length ; i++){
        MCP_send_single_data_byte(MCP_TXB + i, can_block -> data[i]);
    }
    MCP_request_send();
}


Can_block CAN_recieve(uint8_t buffer){
    Can_block received_can_block;

    received_can_block.id = (MCP_read_single_data_byte(MCP_SID0_HIGH) << 3) | (MCP_read_single_data_byte(MCP_SID0_LOW) >> 5);

    received_can_block.length = MCP_read_single_data_byte(MCP_RXB0DLC) & (0x0F);

    for(uint8_t i = 0; i < received_can_block.length; i++){

        received_can_block.data[i] = MCP_read_single_data_byte(MCP_RXB + i);

    }
    return received_can_block;
}

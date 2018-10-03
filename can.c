#include "can.h"
#include "MCP2515.h"
#include <stdio.h>

void CAN_init(void){

    MCP_send_single_data_byte(MCP_CANCTRL, MODE_LOOPBACK);

}

void CAN_send(Can_block* can_block){
    MCP_send_single_data_byte(MCP_TXB0CTRL, can_block -> id);
    MCP_send_single_data_byte(0x32, 0x00);
    MCP_send_single_data_byte(MCP_TXB0CTRL + 5, can_block -> length); //Set data length

    for(int i = 0; i < can_block -> length ; i++){
        MCP_send_single_data_byte(MCP_TXB0CTRL + 6 + i, can_block -> data[i]);
    }
    MCP_request_send();
}

#include "can.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "node_setup.h"


void CAN_init(void){

    MCP_bit_modify(MCP_RXB0CTRL, 0b01100000, 0xFF);
    MCP_send_single_data_byte(MCP_CANCTRL, MODE_NORMAL);

    CAN_message_interrupt_init();


}

int CAN_send(Can_block* can_block){
    //MCP_bit_modify(MCP_TXB0CTRL, 0b00000111, 0x07);
    if(CAN_clear_to_send()){
        MCP_send_single_data_byte(MCP_SID0_HIGH, can_block -> id >> 3);
        MCP_send_single_data_byte(MCP_SID0_LOW, can_block -> id << 5);
        MCP_send_single_data_byte(MCP_RXB0DLC, (can_block -> length) & (0x0F) ); //Set data length

        for(int i = 0; i < can_block -> length ; i++){
            MCP_send_single_data_byte(MCP_TXB + i, can_block -> data[i]);
        }
        MCP_request_send();
    }
    else{
        if (CAN_error() != 0){
            return CAN_error();
        }
    }
    return 0;
}


Can_block CAN_recieve(uint8_t buffer){
    Can_block received_can_block;


    received_can_block.id = (MCP_read_single_data_byte(MCP_SID0_HIGH) << 3) | (MCP_read_single_data_byte(MCP_SID0_LOW) >> 5);

    received_can_block.length = MCP_read_single_data_byte(MCP_RXB0DLC) & (0x0F);

    for(uint8_t i = 0; i < received_can_block.length; i++){
        received_can_block.data[i] = MCP_read_single_data_byte(MCP_RXB + i);
    }
    CAN_reset_interrupt_flag();
    printf("%d\n", MCP_read_single_data_byte(0x2C));

    return received_can_block;
}

int CAN_clear_to_send(){
    // If bit 3 in control register TXB0 is 0, the buffer is ready to send
    return !(test_bit(MCP_read_single_data_byte(MCP_TXB0CTRL), 0x03));
}

int CAN_error(){
    if(test_bit(MCP_read_single_data_byte(MCP_TXB0CTRL), 0x04)){
        return -1; //Error in TXREQ, transmitting error.
    }
    if(test_bit(MCP_read_single_data_byte(MCP_TXB0CTRL), 0x05)){
        return -2; // MLOA: message lost in arbritition.
    }
    return 0;
}


void CAN_reset_interrupt_flag(){
    MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);
}

void CAN_message_interrupt_init(){
    MCP_bit_modify(MCP_CANINTE, 0x01, 0xFF); //Interupt enable
    MCUCR = (1 << ISC01) | (1 << ISC00);
    sei();
}

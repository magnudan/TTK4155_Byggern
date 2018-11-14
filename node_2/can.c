#include "can.h"
#include "MCP2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "node_setup.h"

#define MCP_SID0_HIGH   0x31
#define MCP_SID0_LOW    0x32
#define MCP_RXB0DLC     0x65
#define MCP_RXB1DLC     0x75
#define MCP_TXB0DLC     0x35
#define MCP_TXB1DLC     0x45
#define MCP_RXB         0x66
#define MCP_TXB         0x36

#define MCP_TX_PRI_BITS          0b00000011
#define MCP_DATA_LENGTH_BITS     0b00001111
#define MCP_RX_BUFF_OP_MODE_BITS 0b01100000
#define MCP_MSG_LOST_ARB_BIT     5
#define MCP_TX_ERR_DETECTED_BIT  4
#define MCP_MSG_TX_REQ_BIT       3
#define MCP_RX_BUFF0_FULL_FLAG   0b00000001
#define MCP_RX_BUFF0_FULL_ENABLE 0b00000001


void CAN_init(void){
    MCP_bit_modify(MCP_RXB0CTRL, MCP_RX_BUFF_OP_MODE_BITS, 0xFF);
    MCP_send_single_data_byte(MCP_CANCTRL, MODE_NORMAL);

    CAN_message_interrupt_init();
}

int CAN_send(Can_block* can_block){
    MCP_bit_modify(MCP_TXB0CTRL, MCP_TX_PRI_BITS, 0x03);

    if(CAN_clear_to_send()){
        MCP_send_single_data_byte(MCP_SID0_HIGH, can_block -> id >> 3);
        MCP_send_single_data_byte(MCP_SID0_LOW, can_block -> id << 5);
        MCP_send_single_data_byte(MCP_TXB0DLC, (can_block -> length) & (0x0F) ); //Set data length

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

    received_can_block.id = (MCP_read_single_data_byte(MCP_SID0_HIGH) << 3)
                          | (MCP_read_single_data_byte(MCP_SID0_LOW) >> 5);
    received_can_block.length = (MCP_read_single_data_byte(MCP_RXB0DLC)) & (MCP_DATA_LENGTH_BITS);


    for(uint8_t i = 0; i < received_can_block.length; i++){
        received_can_block.data[i] = MCP_read_single_data_byte(MCP_RXB + i);
    }
    CAN_reset_interrupt_flag();

    return received_can_block;
}

int CAN_clear_to_send(){
    // If bit 3 in control register TXB0 is 0, the buffer is ready to send
    return !(test_bit(MCP_read_single_data_byte(MCP_TXB0CTRL), MCP_MSG_TX_REQ_BIT));
}

int CAN_error(){

    if(test_bit(MCP_read_single_data_byte(MCP_TXB0CTRL), MCP_TX_ERR_DETECTED_BIT)){
        return -1; //Error in TXREQ, transmitting error.
    }
    if(test_bit(MCP_read_single_data_byte(MCP_TXB0CTRL), MCP_MSG_LOST_ARB_BIT)){
        return -2; // MLOA: message lost in arbritition.
    }
    return 0;
}


void CAN_reset_interrupt_flag(){
    MCP_bit_modify(MCP_CANINTF, MCP_RX_BUFF0_FULL_FLAG, 0x00);
}

void CAN_message_interrupt_init(){
    MCP_bit_modify(MCP_CANINTE, MCP_RX_BUFF0_FULL_ENABLE, 0xFF);   //Interupt enable
    write_bit(0, EIMSK, INT2);
    write_bit(1, EICRA, ISC21);
    write_bit(0, EICRA, ISC20);
    write_bit(1, EIMSK, INT2);
    write_bit(1, PORTD, PD2);
    sei();
}

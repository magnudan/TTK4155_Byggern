#include "spi.h"
#include <stdio.h>
#include <util/delay.h>
#include "MCP2515.h"

void MCP_init(){
    MCP_reset();
    //MCP_send_single_data_byte(MCP_CANCTRL, MODE_LOOPBACK);
}

void MCP_reset(){
    SPI_select();
    SPI_transmit_byte(MCP_RESET);
    SPI_deselect();
    _delay_ms(200);
}

void MCP_send_single_data_byte(uint8_t address, uint8_t command){
    SPI_select();
    SPI_transmit_byte(MCP_WRITE);
    SPI_transmit_byte(address);
    SPI_transmit_byte(command);
    SPI_deselect();
}

uint8_t MCP_read_single_data_byte(uint8_t address){
    SPI_select();
    SPI_transmit_byte(MCP_READ);
    SPI_transmit_byte(address);
    uint8_t data = SPI_recieve_byte();
    SPI_deselect();
    return data;
}


/*
uint64_t MCP_read_RX_buffer_test(void){
    SPI_select();
    SPI_transmit_byte(MCP_READ_RX0);
    uint8_t recieved_byte = SPI_recieve_byte();
    SPI_deselect();
    return recieved_byte;
}
*/



void MCP_read_RX_buffer(uint8_t data[], uint8_t length){
    SPI_select();
    SPI_transmit_byte(MCP_READ_RX0);
    for(int i = 0; i < length; i++){
        data[i] = SPI_recieve_byte();
        //buffer_data |= (recieved_byte << (8*i));
    }
    SPI_deselect();
    //return buffer_data;
}


void MCP_load_TX_buffer(uint64_t data){
    SPI_select();
    SPI_transmit_byte(MCP_LOAD_TX0);
    for(int i = 0; i < 8; i++){ //LØØÔÕP
        uint8_t byte = MCP_get_byte(data, i);
        SPI_transmit_byte(MCP_get_byte(data, i));
    }
    SPI_deselect();
}


void MCP_request_send(void){
    SPI_select();
    SPI_transmit_byte(MCP_RTS_TX0);
    SPI_deselect();
}

uint8_t MCP_read_status(void){
    SPI_select();
    SPI_transmit_byte(MCP_READ_STATUS);
    uint8_t status = SPI_recieve_byte();
    SPI_deselect();
    return status;
}

void MCP_bit_modify(uint8_t register_to_modify, uint8_t mask, uint8_t data){
    SPI_select();
    SPI_transmit_byte(MCP_bit_modify);
    SPI_transmit_byte(mask);
    SPI_transmit_byte(data);
    SPI_deselect();

}


uint8_t MCP_get_byte(uint64_t data, uint8_t byte_nr){
    return (data >> (8*byte_nr)) & (0xFF);
}

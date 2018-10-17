//#define F_CPU 16000000UL
#include "node_setup.h"
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/io.h>
#include "can.h"
#include "MCP2515.h"
#include "spi.h"

void main(){
    uart_init();
    /*DDRF |= (1<<PF0);
    while(1){
        _delay_ms(5);
        printf("hello\r\n");
    }*/
    SPI_init();
    MCP_init();
    CAN_init();
    Can_block my_can_block = {1, 3, { 0xFF, 0xAA, 0x00}};
    while(1){
      //printf("%d\n", CAN_send(&my_can_block));
      //CAN_reset_interrupt_flag();
      //CAN_reset_interrupt_flag();
      /*
      CAN_send(&my_can_block);
      _delay_ms(200);
      Can_block my_other_can_block = CAN_recieve(1);
      //printf("%0x16d\r\n", my_other_can_block.length);
      for(int i = 0; i < my_other_can_block.length; i++){
          printf("(%d)\r\n", my_other_can_block.data[i]);
      }
      //printf("%d\r\n", MCP_read_status());
      _delay_ms(300);
      */

      _delay_ms(10);
      SPI_select();
      _delay_ms(200);
      SPI_deselect();
      _delay_ms(190);
      //CAN_reset_interrupt_flag();

      //printf("%d\n", MCP_read_single_data_byte(MCP_CANINTF));
      //printf("%d\n", MCP_read_single_data_byte(0x2C));
      /*_delay_ms(300);
      //printf("%d\n", MCP_read_single_data_byte(0x2C));
      Can_block my_other_can_block = CAN_recieve(1);
      //printf("%0x16d\r\n", my_other_can_block.length);
      for(int i = 0; i < my_other_can_block.length; i++){
          //printf("(%d)\r\n", my_other_can_block.data[i]);
      }*/
      //printf("test");

      //CAN_reset_interrupt_flag();
    }
}

ISR(INT0_vect){
    Can_block my_other_can_block = CAN_recieve(1);
    //printf("%0x16d\r\n", my_other_can_block.length);
    for(int i = 0; i < my_other_can_block.length; i++){
        printf("(%d)\r\n", my_other_can_block.data[i]);
    }
}

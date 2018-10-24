//#define F_CPU 16000000UL
#include "node_setup.h"
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "can.h"
#include "MCP2515.h"
#include "spi.h"
#include "pwm.h"
#include "TWI_Master.h"
#include "dac.h"

void main(){
    uart_init();
    SPI_init();
    MCP_init();
    CAN_init();
    PWM_init();
    DAC_init();
    //TWCR = (1<<TWIE)|(1<<TWINT);

    uint8_t i = 0;
    while(1){
        DAC_send(10);

      //printf("%d\n", CAN_send(&my_can_block));
      //CAN_reset_interrupt_flag();
      //CAN_reset_interrupt_flag();
      /*

      _delay_ms(200);
      printf("%d\r\n", CAN_send(&my_can_block));
      _delay_ms(200);printf("%d\r\n", MCP_read_status());
      printf("%d\n", EIFR);


      Can_block my_other_can_block = CAN_recieve(1);*/
      //CAN_reset_interrupt_flag();
      //Can_block my|_other_can_block = CAN_recieve(1);
      //printf("%0x16d\r\n", my_other_can_block.length);
      //for(int i = 0; i < my_other_can_block.length; i++){
          //printf("(%d)\r\n", my_other_can_block.data[i]);
      //}
      //printf("%d\r\n", MCP_read_status());

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
      //CAN_reset_interrupt_flag()
      _delay_ms(100);
      //printf("Hei\n\r");
  }
}

ISR(INT2_vect){
    Can_block received_can_block = CAN_recieve(1);
    switch (received_can_block.data[0]) {
        case  1:{
            int x_pos = received_can_block.data[1];
            int y_pos = received_can_block.data[2];
            printf("X-position: %d Y-position: %d\r\n",x_pos, y_pos);
            PWM_set_angle(x_pos);
            break;
        }
        default:
            break;
    }

}

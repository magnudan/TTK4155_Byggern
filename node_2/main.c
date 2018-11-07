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
#include "motor_driver.h"
#include "encoder.h"
#include "adc.h"

#define JOYSTICK 1
#define TOUCH 2

void main(){
    uart_init();
    //adc_init();
    PWM_init();
    DAC_init();
    sei();
    motor_init();

    SPI_init();
    MCP_init();
    CAN_init();



    solenoid_init();
    //encoder_init();

    while(1){
        //printf("Motor position: %d\n\r", encoder_read());
        //for (uint8_t i = 0; i < 255; i++){DAC_send(i); _delay_ms(10);}

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
      //printf("Hei\n\r");
      _delay_ms(300);
  }
}

ISR(INT2_vect){
    Can_block received_can_block = CAN_recieve(JOYSTICK);
    switch (received_can_block.data[0]) {
        case JOYSTICK:{
            int x_pos = received_can_block.data[1];
            int y_pos = received_can_block.data[2];
            //printf("X-position: \t%d | Y-position: %d\r\n",x_pos, y_pos);
            PWM_set_angle(y_pos);
            motor_set_speed_from_joystick(x_pos);
            if(received_can_block.data[3] == 1){
                solenoid_punch();
            }
            break;
        }
        case TOUCH :{
            int l_slider = received_can_block.data[1];
            int r_slider = received_can_block.data[2];
            //printf("Left slider: \t%d | Right slider: %d\n\r", l_slider, r_slider);
            //position_regulator(l_slider);
            if (received_can_block.data[3] == 1 || received_can_block.data[4] == 1){
                printf("DIK\n\r");
                solenoid_punch();
            }
            break;
        }
        default:
            break;
    }

}

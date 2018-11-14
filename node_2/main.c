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
#include "timer.h"
#include "score_counter.h"


#define JOYSTICK 1
#define TOUCH 2
#define MOTOR_INIT_CAN 3
uint8_t wolol = 0;

void main(){
    adc_init();
    uart_init();
    //adc_init();
    PWM_init();

    sei();
    DAC_init();
    motor_init();

    SPI_init();
    MCP_init();
    CAN_init();
    timer_init();


    solenoid_init();
    //encoder_init();
    score_counter_init();
    while(1){
      //Can_block my_can_block  = {1, 2, {0xFF, 0xDA}};
      //printf("Data from CAN: %d\r\n", encoder_read() << 8 + encoder_read());
      //CAN_send(&my_can_block);

      //score_counter_update();
      score_counter_update();
      printf("Score: %d\r\n", score_counter_get());
      _delay_ms(300);

  }
}

uint8_t position_reference;

ISR(INT2_vect){
    Can_block received_can_block = CAN_recieve(JOYSTICK);
    switch (received_can_block.data[0]) {
        case JOYSTICK:{
            int x_pos = received_can_block.data[1];
            int y_pos = received_can_block.data[2];
            int joystick_button = received_can_block.data[3];
            //printf("X-position: \t%d | Y-position: %d\r\n",x_pos, y_pos);
            PWM_set_angle(x_pos);
            if (joystick_button == 1){
                score_counter_reset();
            }
            //motor_set_speed_from_joystick(x_pos);
            //solenoid_punch(received_can_block.data[3]);
            break;
        }
        case TOUCH :{
            int l_slider = received_can_block.data[1];
            int r_slider = received_can_block.data[2];
            position_reference = l_slider;
            //PWM_set_angle(r_slider);
            solenoid_punch(received_can_block.data[3]);
            break;
        }
        case MOTOR_INIT_CAN :{
            //motor_init();
            break;
        }
        default:
            break;
    }

}


ISR(TIMER3_COMPA_vect){
    position_regulator(position_reference);
    TCNT3 = 0x0000;
}

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
#include "fail_counter.h"
#include "analog_controller.h"

#define JOYSTICK 1
#define TOUCH 2
#define RESET_NODE_2 3
#define CASE_4 4
#define CASE_5 5

enum STATE {STOP, RUN_POSITION, RUN_SPEED, RUN_UDP_SPEED};
uint8_t position_reference = 0;
char instruction;

enum STATE state = STOP;

void main(){
    write_bit(1, DDRB, PB4);
    write_bit(1, PORTB, PB4); //??
    adc_init();
    uart_init();
    PWM_init();

    sei();
    DAC_init();

    motor_init();
    SPI_init();
    MCP_init();
    CAN_init();

    solenoid_init();
    fail_counter_init();
    analog_controller_init();
    timer_init();


    while(1){



      _delay_ms(100);

      // If a game is running, send score to node 1
      if(state != STOP){
        fail_counter_update();
      }
      else if(state == STOP){
          PWM_set_angle(128);
          motor_set_speed(0);
      }
  }
}


// Short description of what the interrupt routine does
ISR(INT2_vect){
    Can_block received_can_block = CAN_recieve(JOYSTICK);
    switch (received_can_block.data[0]) {
        case JOYSTICK:{

            int x_pos = received_can_block.data[1];
            int y_pos = received_can_block.data[2];
            int joystick_button = received_can_block.data[3];
            PWM_set_angle(x_pos);
            break;
        }
        case TOUCH :{
            state = RUN_POSITION;
            int l_slider = received_can_block.data[1];
            position_reference = l_slider;
            solenoid_punch(received_can_block.data[3]);

            break;
        }
        case RESET_NODE_2 :{
            if(received_can_block.data[1] == 4 && received_can_block.data[2] == 5){
                // MAaaAGigGGc N U M B E R S
              printf("CAN reset: \r\n");
              write_bit(0, PORTB, PB4);
            }
            break;
        }
        case CASE_4:{
          encoder_init();
          state = RUN_SPEED;
          break;
        }
        case CASE_5:{
          state = STOP;
          break;
        }
        case 6:{
            state = RUN_UDP_SPEED;
            break;
        }
        default:
            break;
    }

}

// Short description of what the interrupt routine does
ISR(TIMER3_COMPA_vect){

    if(state == RUN_POSITION){
      position_regulator(position_reference);
    }
    else if (state == RUN_SPEED){
      analog_speed_control();
    }
    else if (state == RUN_UDP_SPEED){
        switch(instruction){
            case 'a':{
                speed_regulator(30, -1);
                break;
            }
            case 'b':{
                speed_regulator(0, 0);
                break;
            }
            case 'c':{
                speed_regulator(30, 1);
                break;
            }
            case 'd':{
                speed_regulator(0, 0);
                break;
            }
            case 'e':{
                PWM_move_left(1);
                break;
            }
            case 'f':{
                PWM_move_left(0);
                break;
            }
            case 'g':{
                PWM_move_right(1);
                break;
            }
            case 'h':{
                PWM_move_right(0);
                break;
            }
            case 'i':{
                solenoid_punch(1);
                break;
            }
            case 'j':{
                solenoid_punch(0);
                break;
            }
        }
    }


    TCNT3 = 0x0000; // What is this?

}

ISR(USART0_RX_vect){
    instruction = UDR0;
}

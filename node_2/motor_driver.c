#include "motor_driver.h"
#include "dac.h"
#include "node_setup.h"
#include <avr/io.h>
#include <util/delay.h>

#define JOYSTIC_THRESHOLD_LEFT 127
#define JOYSTIC_THRESHOLD_RIGHT 132


void motor_init(){
    set_bit(DDRH, PH4); //Enable motor
    set_bit(PORTH, PH4);
    set_bit(DDRH, PH1);
}

void motor_set_direction_left(){
    clear_bit(PORTH, PH1);
}

void motor_set_direction_right(){
    set_bit(PORTH, PH1);
}

void motor_set_speed(uint8_t speed){
    DAC_send(speed);
}

void motor_set_speed_from_joystick(uint8_t joystick_output){
    if (joystick_output < JOYSTIC_THRESHOLD_LEFT){
        motor_set_direction_left();
        DAC_send(150);
    }
    else if(joystick_output > JOYSTIC_THRESHOLD_RIGHT){
        motor_set_direction_right();
        DAC_send(150);
    }
    else {
        DAC_send(0);
    }
}

void solenoid_init(){
    set_bit(DDRB, PB6);
    set_bit(PORTB, PB6);
}

void solenoid_punch(){
    clear_bit(PORTB, PB6);
    _delay_ms(100);
    set_bit(PORTB, PB6);
}

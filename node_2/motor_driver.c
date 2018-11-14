#include "motor_driver.h"
#include "dac.h"
#include "node_setup.h"
#include "encoder.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define JOYSTIC_THRESHOLD_LEFT 127
#define JOYSTIC_THRESHOLD_RIGHT 132
#define MOTOR_STOP 0
#define MOTOR_INIT_SPEED 100
#define MAGIC_FRACTION 39

#define T_POS   1/50
#define KP_POS  3
#define KI_POS  1
#define KD_POS  3

#define T_SAMPLE  0.0000001
#define T_SPEED   0.1
#define KP_SPEED  0.7
#define KI_SPEED  0
#define KD_SPEED


void motor_init(){
    set_bit(DDRH, PH4); //Enable motor
    set_bit(PORTH, PH4);
    set_bit(DDRH, PH1);


    cli();
    _delay_ms(10);
    motor_set_direction_left();
    motor_set_speed(MOTOR_INIT_SPEED);
    _delay_ms(2000);
    encoder_init();
    motor_set_speed(MOTOR_STOP);
    sei();

}

void motor_set_direction_left(){
    clear_bit(PORTH, PH1);
}

void motor_set_direction_right(){
    set_bit(PORTH, PH1);
}

void motor_set_speed(uint8_t speed){
    DAC_send(speed);
    //printf("Motor speed is set to: %d\n\r", speed);
}

void motor_set_speed_from_joystick(uint8_t joystick_output){
    uint8_t speed;
    if (joystick_output < JOYSTIC_THRESHOLD_LEFT){
        motor_set_direction_left();
        speed = JOYSTIC_THRESHOLD_LEFT - joystick_output;
        speed_regulator(speed);
        //motor_set_speed(speed);
    }
    else if(joystick_output > JOYSTIC_THRESHOLD_RIGHT){
        motor_set_direction_right();
        speed = joystick_output - JOYSTIC_THRESHOLD_RIGHT;
        speed_regulator(speed);
        //motor_set_speed(speed);
    }
    else {
        motor_set_speed(MOTOR_STOP);
    }
}

void solenoid_init(){
    set_bit(DDRB, PB6);
    set_bit(PORTB, PB6);
}

void solenoid_punch(int signal){
    if (signal == 1){
      clear_bit(PORTB, PB6);
      //_delay_ms(100);
    } else if (signal == 0){
      set_bit(PORTB, PB6);
      //_delay_ms(100);
    }
}


void position_regulator(uint8_t ref_position){
    static int integrator = 0;
    static int last_error = 0;
    uint8_t pos = (uint8_t)(encoder_read() / MAGIC_FRACTION);
    int error = ref_position - pos;
    integrator += error;
    int derivative = error - last_error;
    int new_speed = KP_POS*error + (int)(KI_POS*T_POS*integrator) + KD_POS/T_POS*derivative;
    if (new_speed < 0){
        motor_set_direction_left();
    } else {
        motor_set_direction_right();
    }
    motor_set_speed(abs(new_speed));
    last_error = error;
}

void speed_regulator(int8_t ref_speed){
    static int integrator = 0;
    static uint8_t prev_pos;
    uint8_t pos = (uint8_t)(encoder_read()/MAGIC_FRACTION);
    int8_t speed = (int8_t)((pos - prev_pos)/(T_SAMPLE));
    int error = ref_speed - speed;
    integrator += T_SPEED*error;
    int8_t new_speed = KP_SPEED*error + T_SPEED*KI_SPEED*integrator;
    //printf("Old pos: %d\n\r", prev_pos);
    //printf("New pos: %d\n\r", pos);
    printf("Error: %d\t", error);
    printf("Integrator: %d\t", integrator);
    //printf("Ref speed: %d\n\r", ref_speed);
    //printf("Act speed: %d\n\r", speed);
    printf("Set speed: %d\n\r", new_speed);
    //printf("-------\n\r");
    motor_set_speed(new_speed);
    prev_pos = pos;
}

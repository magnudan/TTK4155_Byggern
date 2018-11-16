#include "motor_driver.h"
#include "dac.h"
#include "node_setup.h"
#include "encoder.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MOTOR_PIN    PH4
#define DIR_PIN      PH1
#define SOLENOID_PIN PB6

#define JOYSTIC_THRESHOLD_LEFT 127
#define JOYSTIC_THRESHOLD_RIGHT 132
#define MOTOR_STOP 0
#define MOTOR_INIT_SPEED 100
#define ENCODER_SCALER 39

#define T   1/50
#define KP_POS  3
#define KI_POS  1
#define KD_POS  3


#define KP_SPEED  2
#define KI_SPEED  0.5
#define KD_SPEED  1


void motor_init(){
    write_bit(OUTPUT, DDRH, MOTOR_PIN); //Set data direction
    write_bit(1, PORTH, MOTOR_PIN);     //Enable motor
    write_bit(OUTPUT, DDRH, DIR_PIN);   //Set data direction



    _delay_ms(10);
    motor_set_direction_left();
    motor_set_speed(MOTOR_INIT_SPEED);
    _delay_ms(2000);
    encoder_init();
    motor_set_speed(MOTOR_STOP);
}

void motor_set_direction_left(){
    write_bit(0, PORTH, DIR_PIN);
}

void motor_set_direction_right(){
    write_bit(1, PORTH, DIR_PIN);
}

void motor_set_speed(uint8_t speed){
    DAC_send(speed);
    //printf("Motor speed is set to: %d\n\r", speed);
}

//To be used with the joystick from USB mulitfunction card.
//Slight tuning of the joystick threshold may be needed.
void motor_set_speed_from_joystick(uint8_t joystick_output){
    uint8_t speed;
    if (joystick_output < JOYSTIC_THRESHOLD_LEFT){
        motor_set_direction_left();
        speed = JOYSTIC_THRESHOLD_LEFT - joystick_output;
        speed_regulator(speed);
    }
    else if(joystick_output > JOYSTIC_THRESHOLD_RIGHT){
        motor_set_direction_right();
        speed = joystick_output - JOYSTIC_THRESHOLD_RIGHT;
        speed_regulator(speed);
    }
    else {
        motor_set_speed(MOTOR_STOP);
    }
}

void solenoid_init(){
    write_bit(OUTPUT, DDRB, SOLENOID_PIN); //Set data direction
    write_bit(1, PORTB, SOLENOID_PIN);     //Enable solenoid
}

void solenoid_punch(int signal){
    if (signal == 1){
      //Set pin to low to activate solenoid
      write_bit(0, PORTB, SOLENOID_PIN);
    } else if (signal == 0){
      //Set pin to high to deactivate solenoid
      write_bit(1, PORTB, SOLENOID_PIN);
    }
}

//Discrete implementation of a PID-regulator
void position_regulator(uint8_t ref_position){
    static int integrator = 0;
    static int prev_error = 0;

    uint8_t position = (uint8_t)(encoder_read() / ENCODER_SCALER);
    int error = ref_position - position;
    int derivative = error - prev_error;
    integrator += error;

    int new_speed = KP_POS*error + (int)(KI_POS*T*integrator) + KD_POS/T*derivative;

    if (new_speed < 0){
        motor_set_direction_left();
    } else {
        motor_set_direction_right();
    }

    motor_set_speed(abs(new_speed));

    prev_error = error;
}

//Discrete implementation of a PID-regulator
void speed_regulator(int8_t ref_speed){
    static int integrator = 0;
    static uint8_t prev_position = 0;
    static int prev_error = 0;

    uint8_t position = (uint8_t)(encoder_read()/ENCODER_SCALER);
    int8_t speed = (int8_t)(position - prev_position);

    int error = ref_speed - speed;
    int derivative = error - prev_error;
    integrator += error;

    int8_t new_speed = KP_SPEED*error + T*KI_SPEED*integrator + KD_SPEED/T*derivative;

    motor_set_speed(new_speed);
    prev_position = position;
    prev_error = error;
}

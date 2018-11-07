#include "motor_driver.h"
#include "dac.h"
#include "node_setup.h"
#include "encoder.h"
#include <avr/io.h>
#include <util/delay.h>

#define JOYSTIC_THRESHOLD_LEFT 127
#define JOYSTIC_THRESHOLD_RIGHT 132
#define MOTOR_STOP 0
#define MOTOR_INIT_SPEED 50
#define KP_POS  0.1
#define T 0.001
#define KI_POS 1
#define KD_POS
#define MAGIC_FRACTION 40
#define KP_SPEED 0.1
#define KI_SPEED 0.1
#define KD_SPEED


void motor_init(){
    set_bit(DDRH, PH4); //Enable motor
    set_bit(PORTH, PH4);
    set_bit(DDRH, PH1);

    _delay_ms(10);
    motor_set_direction_left();
    motor_set_speed(MOTOR_INIT_SPEED);
    _delay_ms(2000);
    motor_set_speed(MOTOR_STOP);
    _delay_ms(500);
    encoder_init();

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
        //speed_regulator(speed);
        motor_set_speed(speed);
    }
    else if(joystick_output > JOYSTIC_THRESHOLD_RIGHT){
        motor_set_direction_right();
        speed = joystick_output - JOYSTIC_THRESHOLD_RIGHT;
        //speed_regulator(speed);
        motor_set_speed(speed);
    }
    else {
        motor_set_speed(MOTOR_STOP);
    }
}

void solenoid_init(){
    set_bit(DDRB, PB6);
    set_bit(PORTB, PB6);
}

void solenoid_punch(){
    clear_bit(PORTB, PB6);
    _delay_ms(200);
    set_bit(PORTB, PB6);
}


void position_regulator(uint8_t ref_position){
    static uint8_t integrator;
    int8_t error;
    int16_t pos = encoder_read();
    error = ref_position - (uint8_t)(pos / MAGIC_FRACTION);
    integrator += error;
    int8_t new_speed = KP_POS*error + T*KI_POS*integrator;
    printf("Ref pos: %d\n\r", ref_position);
    printf("Act pos: %d\n\r", pos);
    printf("Magic number: %d\r\n", (uint8_t)(pos / MAGIC_FRACTION));
    printf("Error: %d\n\r", error);
    printf("Integrator: %d\r\n", integrator);
    printf("Set speed: %d\n\r", new_speed);
    printf("-------\n\r");
    if (ref_position < pos){
        motor_set_direction_left();
    } else {
        motor_set_direction_right();
    }
    motor_set_speed(new_speed);
}

void speed_regulator(int8_t ref_speed){
    static uint8_t integrator = 0;
    static uint16_t prev_pos;
    int16_t pos = encoder_read();
    int8_t speed = (uint8_t)((pos - prev_pos)/(MAGIC_FRACTION*T));
    int8_t error = ref_speed - speed;
    integrator += error;
    int8_t new_speed = KP_SPEED*error + T*KI_SPEED*integrator;
    printf("Old pos: %d\n\r", prev_pos);
    printf("New pos: %d\n\r", pos);
    printf("Error: %d\n\r", error);
    printf("Integrator: %d\r\n", integrator);
    printf("Ref speed: %d\n\r", ref_speed);
    printf("Act speed: %d\n\r", speed);
    printf("Set speed: %d\n\r", new_speed);
    printf("-------\n\r");
    motor_set_speed(new_speed);
    prev_pos = pos;
}

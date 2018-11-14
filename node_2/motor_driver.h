#ifndef motor_driver_H_
#define motor_driver_H_

#include <avr/io.h>

#endif

void motor_init();
void motor_set_direction_left();
void motor_set_direction_right();
void motor_set_speed(uint8_t speed);

//To be used with the joystick from USB mulitfunction card.
//Slight tuning of the joystick threshold may be needed.
void motor_set_speed_from_joystick(uint8_t joystick_output);


void solenoid_init();
void solenoid_punch(int signal);

//Discrete implementations of PID-regulators
void position_regulator(uint8_t ref_position);
void speed_regulator(int8_t ref_speed);

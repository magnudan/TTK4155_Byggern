#ifndef analog_controller_H_
#define analog_controller_H_

#include <avr/io.h>

#endif

void analog_controller_init();
uint8_t analog_controller_get_down();
uint8_t analog_controller_get_left();
uint8_t analog_controller_get_up();
uint8_t analog_controller_get_right();
uint8_t analog_controller_get_button();

void analog_speed_control();

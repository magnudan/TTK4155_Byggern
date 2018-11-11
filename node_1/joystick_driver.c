#include "can.h"
#include "adc.h"
#include "button.h"
#include <avr/io.h>

#define JOYSTICK 1
#define TOUCH 2

void joystick_send(){
    int what_to_send = JOYSTICK;
    Can_block joystick_position = {1, 4, {what_to_send, adc_read_channel(JOYSTICK_X), adc_read_channel(JOYSTICK_Y), button_read(BUTTON_JOYSTICK)}};
    CAN_send(&joystick_position);
}

void touch_send(){
    int what_to_send = TOUCH;
    Can_block touch = {1, 5, {what_to_send, adc_read_channel(SLIDER_L), adc_read_channel(SLIDER_R), button_read(BUTTON_L), button_read(BUTTON_R)}};
    CAN_send(&touch);
}

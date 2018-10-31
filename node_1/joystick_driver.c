#include "can.h"
#include "adc.h"
#include "button.h"
#include <avr/io.h>

void joystick_send(){
    int what_to_do = 1;
    Can_block joystick_position = {1, 4, {what_to_do, adc_read_channel(JOYSTICK_X), adc_read_channel(JOYSTICK_Y), button_read(BUTTON_JOYSTICK)}};
    CAN_send(&joystick_position);
}

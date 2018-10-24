#include "can.h"
#include "adc.h"

void joystick_send_position(){
    int what_to_do = 1;
    Can_block joystick_position = {1, 3, {what_to_do, adc_read_channel(JOYSTICK_X), adc_read_channel(JOYSTICK_Y)}};
    CAN_send(&joystick_position);
}

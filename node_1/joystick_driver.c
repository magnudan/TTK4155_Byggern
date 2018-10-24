#include "can.h"
#include "adc.h"

void joystick_send_position(){
    Can_block joystick_position = {1, 2, {adc_read_channel(JOYSTICK_X), adc_read_channel(JOYSTICK_Y)}};
    CAN_send(&joystick_position);
}

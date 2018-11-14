#include "can.h"
#include <util/delay.h>
#include "joystick_driver.h"

void game_loop(void){
    Can_block motor_init = {1, 1, {3}};
    CAN_send(&motor_init);
    _delay_ms(2000);
    while(1){
        _delay_ms(10);
        touch_send();
    }
}

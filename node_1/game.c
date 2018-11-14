#include "can.h"
#include <util/delay.h>
#include "joystick_driver.h"

void game_loop(int select_game){
    switch (select_game) {
        case 1:{
            Can_block motor_init = {1, 1, {3}};
            CAN_send(&motor_init);
            uint16_t i = 0;
            while(1){
                _delay_ms(10);
                touch_send();
                joystick_send();
                i++;
                if(i > 1000){
                    return;
                }
            }
            break;
        }
        case 2:{
            Can_block motor_init = {1, 1, {3}};
            CAN_send(&motor_init);
            uint16_t i = 0;
            _delay_ms(10000);
            return;
        }
    }

}

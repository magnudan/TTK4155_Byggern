#include "can.h"
#include <util/delay.h>
#include "joystick_driver.h"

void game_loop_position(void){

      Can_block motor_init = {1, 3, {3, 4, 5}};
      CAN_send(&motor_init);
      uint16_t i = 0;
      while(1){
          _delay_ms(20);
          touch_send();
          joystick_send();
          i++;
          if(i > 10000){
              return;
          }
      }
}

void game_loop_speed(){
    //Can_block motor_init = {1, 3, {3, 4, 5}};
    //CAN_send(&motor_init);
    //delay_ms(10);
    Can_block speed_control = {1, 1,{4}};
    CAN_send(&speed_control);
    int test = 1;
    int i = 0;
    while(test){
      _delay_ms(10);
      i++;
      if(i == 10000){
        test = 0;
      }
    }
    Can_block time_out = {1, 1, {5}};
    CAN_send(&time_out);
    return;
}

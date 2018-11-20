#include "can.h"
#include "oled.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "joystick_driver.h"
#include "button.h"

uint8_t fails = 0;

void game_reset_fails(){
    fails = 0;
}

uint8_t game_get_fails(){
    return fails;
}

void game_increment_fails(){
    fails++;
}

void game_over(){
    Can_block time_out = {1, 1, {5}};
    CAN_send(&time_out);
    game_write_fails_oled();

    oled_next_line();
    if (game_get_fails() >= 5){
        oled_write_line("Too bad. Try again?");
    } else {
        oled_write_line("Nice! Keep up the good work");
    }
    uint8_t last_button_state = button_read(BUTTON_JOYSTICK);
    while (last_button_state != button_read(BUTTON_JOYSTICK)){
        _delay_ms(2);
    }
}

void game_write_fails_oled(){
    char n_fails[3];
    itoa(game_get_fails(), n_fails, 3);

    oled_clear_display();
    oled_write_line("Number of fails");
    oled_write_line(n_fails);
}

void game_write_fails_from_menu(){
    game_write_fails_oled();
    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}


void game_loop_position(void){
      game_reset_fails();
      Can_block motor_init = {1, 3, {3, 4, 5}};
      CAN_send(&motor_init);
      uint16_t i = 0;
      while(1){
          _delay_ms(20);
          touch_send();
          joystick_send();
          i++;
          if(i > 1000){
              cli();
              game_over();
              sei();
              return;
          }
      }
}

void game_loop_speed(){
    game_reset_fails();
    //Can_block motor_init = {1, 3, {3, 4, 5}};
    //CAN_send(&motor_init);
    //delay_ms(10);
    Can_block speed_control = {1, 1,{4}};
    CAN_send(&speed_control);
    int test = 1;
    uint16_t i = 0;
    while(1){
      _delay_ms(20);
      i++;
      if(i > 1000){
          printf("Test\r\n");
          Can_block time_out = {1, 1, {5}};
          CAN_send(&time_out);
          cli();
          game_over();
          sei();
          return;
      }
    }


}

#include "analog_controller.h"
#include "node_setup.h"
#include <avr/io.h>
#include "motor_driver.h"
#include "pwm.h"

#define DOWN_PIN   PA0
#define LEFT_PIN   PA6
#define UP_PIN     PA4
#define RIGHT_PIN  PA2
#define BUTTON_PIN PC7

void analog_controller_init(){
  //Setting data direction to input
  write_bit(INPUT, DDRA, DOWN_PIN);
  write_bit(INPUT, DDRA, LEFT_PIN);
  write_bit(INPUT, DDRA, UP_PIN);
  write_bit(INPUT, DDRA, RIGHT_PIN);
  write_bit(INPUT, DDRC, BUTTON_PIN);

  //Enabling pull-up resistors
  write_bit(1, PORTA, DOWN_PIN);
  write_bit(1, PORTA, LEFT_PIN);
  write_bit(1, PORTA, UP_PIN);
  write_bit(1, PORTA, RIGHT_PIN);
  write_bit(1, PORTC, BUTTON_PIN);
}

uint8_t analog_controller_get_down(){
  return !(test_bit(PINA, DOWN_PIN) >> DOWN_PIN);
}

uint8_t analog_controller_get_left(){
  return !(test_bit(PINA, LEFT_PIN) >> LEFT_PIN);
}

uint8_t analog_controller_get_up(){
  return !(test_bit(PINA, UP_PIN) >> UP_PIN);
}

uint8_t analog_controller_get_right(){
  return !(test_bit(PINA, RIGHT_PIN) >> RIGHT_PIN);
}

uint8_t analog_controller_get_button(){
  return !(test_bit(PINC, BUTTON_PIN) >> BUTTON_PIN);
}


void analog_speed_control(){
    solenoid_punch(analog_controller_get_button());
    if(analog_controller_get_left()){
      printf("Zoop\r\n");
      speed_regulator(100);
      motor_set_direction_left();
    }
    else if(analog_controller_get_right()){
      printf("loop\r\n");
      speed_regulator(100);
      motor_set_direction_right();
    }
    else{
      speed_regulator(0);
    }
    PWM_move_left(analog_controller_get_down());
    PWM_move_right(analog_controller_get_up());
}

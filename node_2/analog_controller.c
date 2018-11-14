#include "analog_controller.h"
#include "node_setup.h"
#include <avr/io.h>

#define DOWN_PIN   PG5
#define LEFT_PIN   PE5
#define UP_PIN     PE4
#define RIGHT_PIN  PE1
#define BUTTON_PIN PE0

void analog_controller_init(){
  //Setting data direction to input
  write_bit(INPUT, DDRG, DOWN_PIN);
  write_bit(INPUT, DDRE, LEFT_PIN);
  write_bit(INPUT, DDRE, UP_PIN);
  write_bit(INPUT, DDRE, RIGHT_PIN);
  write_bit(INPUT, DDRE, BUTTON_PIN);

  //Enabling pull-up resistors
  write_bit(1, PORTG, DOWN_PIN);
  write_bit(1, PORTE, LEFT_PIN);
  write_bit(1, PORTE, UP_PIN);
  write_bit(1, PORTE, RIGHT_PIN);
  write_bit(1, PORTE, BUTON_PIN);
}

uint8_t analog_controller_get_down(){
  return test_bit(DDRG, DOWN_PIN);
}

uint8_t analog_controller_get_left(){
  return test_bit(DDRE, LEFT_PIN);
}

uint8_t analog_controller_get_up(){
  return test_bit(DDRE, UP_PIN);
}

uint8_t analog_controller_get_right(){
  return test_bit(DDRE, RIGHT_PIN);
}

uint8_t analog_controller_get_button(){
  return test_bit(DDRE, BUTTON_PIN);
}

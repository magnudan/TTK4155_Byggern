#include "pwm.h"
#include "node_setup.h"
#include <avr/io.h>


void pwm_init(){
      //set data direction for pin 3 to output
      write_bit(1, DDRD, PD4);

      //sets timer 0 to FAST PWM mode
      write_bit(1, TCCR3A, WGM31);
      write_bit(1, TCCR3B, WGM32);
      write_bit(1, TCCR3B, WGM33);

      //set interrupt flag on overflow
      write_bit(1, TCCR3A, COM3A1);

      //set output compare register to reasonable value
      OCR3A=0x7000;

      //set clock source to CPU/64
      write_bit(1, TCCR3B, CS30);
      write_bit(1, TCCR3B, CS31);

      ICR3 =  0xFFFF;
}

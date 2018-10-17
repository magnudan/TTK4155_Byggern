
#include "node_setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PWM_PERIOD_MS 8
#define OCR1A_MIN 1844
#define OCR1A_MAX 4300
void PWM_init();
void PWM_set_angle(uint8_t angle);


//opens pwm on PB5
void PWM_init(){
    //set data direction for pin 5 to output
    DDRB = (1<<PB5);
    //sets timer 0 to FAST PWM mode
    TCCR1A = TCCR1A | (1<<WGM11);
    TCCR1B = TCCR1B | (1<<WGM12) | (1<<WGM13);
    //set interrupt flag on overflow
    TCCR1A = TCCR1A | (1<<COM1A1);
    //set output compare register to reasonable value
    OCR1A=0x7FFF;
    //set clock source to CPU/1023
    TCCR1B = TCCR1B | (1<<CS11);
    ICR1 =  0x9FFF; 
}

//takes a value between 0 and 255
void PWM_set_angle(uint8_t angle){
    //m A gI C   N u M b e e R S
    OCR1A = 10*angle+OCR1A_MIN; 
}



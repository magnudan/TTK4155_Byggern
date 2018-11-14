
#include "node_setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pwm.h"

#define PWM_PERIOD_MS 8
#define PWM_SCALER 10
#define OCR1A_MIN 1844
#define OCR1A_MAX 4300



//opens pwm on PB5
void PWM_init(){

    //set data direction for pin 5 to output
    write_bit(OUTPUT, DDRB, PB5);

    //sets timer 0 to FAST PWM mode
    write_bit(1, TCCR1A, WGM11);
    write_bit(1, TCCR1B, WGM12);
    write_bit(1, TCCR1B, WGM13);

    //set interrupt flag on overflow
    write_bit(1, TCCR1A, COM1A1);

    //set output compare register to reasonable value
    OCR1A=0x7FFF;

    //set clock source to CPU/1023
    write_bit(1, TCCR1B, CS11);

    ICR1 =  0x9FFF;

    //initialize to idle position
    PWM_set_angle(128);
}

//takes a value between 0 and 255
void PWM_set_angle(uint8_t angle){
    //m A gI C   N u M b e e R S
    OCR1A = PWM_SCALER*angle+OCR1A_MIN;
}

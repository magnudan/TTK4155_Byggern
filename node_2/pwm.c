#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PWM_PERIOD_MS 8
#define PWM_PRESCALER 

void PWM_init();

int main(void){
    PWM_init();
    
    OCR1A = 1844;
    while (1){
        if(OCR1A >= 4300){
            OCR1A = 1844;
        }
        OCR1A++;
        _delay_ms(1);
    }

}

/*
ISR(TIMER1_COMPA_vect){
    PORTB = 0x00;
}
ISR(TIMER1_OVF_vect){
    PORTB = 0xFF;
}
*/


//opens pwm on PB5
void PWM_init(){
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





#include "timer.h"
#include "utils.h"
#include <avr/io.h>
void timer_init()
{
    // Set timer to reset when count reaches  OCR1A 
    bit_write(1, TCCR1A, WGM12);

    // Set clock to internal clock / 1024
    bit_write(1, TCCR1B, CS12);
    bit_write(0, TCCR1B, CS11);
    bit_write(1, TCCR1B, CS10);
    
    // Set compare register to random value
    OCR1A = 0x00FF;

    // Enable compare match interrupt
    bit_write(1, TIMSK1, OCIE1A);
}

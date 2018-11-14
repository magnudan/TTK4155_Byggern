#include "timer.h"
#include "node_setup.h"
#include <avr/io.h>
void timer_init()
{
    // Set timer to reset when count reaches  OCR1A
    write_bit(1, TCCR3A, WGM32);

    // Set clock to internal clock / 1024
    write_bit(1, TCCR3B, CS32);
    write_bit(0, TCCR3B, CS31);
    write_bit(1, TCCR3B, CS30);

    // Set compare register to random value
    OCR3A = 0x013B;

    // Enable compare match interrupt
    write_bit(1, TIMSK3, OCIE3A);
}

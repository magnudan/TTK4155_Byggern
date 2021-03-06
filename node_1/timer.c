#include "timer.h"
#include "node_setup.h"
#include <avr/io.h>
void timer_init()
{
    // Set timer to reset when count reaches  OCR1A
    write_bit(0, TCCR1A, WGM10);
    write_bit(0, TCCR1A, WGM11);
    write_bit(1, TCCR1B, WGM12);
    write_bit(0, TCCR1B, WGM13);

    // Set clock to internal clock / 1024
    write_bit(1, TCCR1B, CS12);
    write_bit(0, TCCR1B, CS11);
    write_bit(1, TCCR1B, CS10);

    // Set compare register to random value
    OCR1A = 0x0080;

    // Enable compare match interrupt
    write_bit(1, TIMSK, OCIE1A);
}

void game_timer_init() {
    // Set timer to reset when count reaches  OCR1A
    write_bit(0, TCCR3A, WGM30);
    write_bit(0, TCCR3A, WGM31);
    write_bit(1, TCCR3B, WGM32);
    write_bit(0, TCCR3B, WGM33);

    // Set clock to internal clock / 1024
    write_bit(1, TCCR3B, CS32);
    write_bit(0, TCCR3B, CS31);
    write_bit(1, TCCR3B, CS30);

    // Set compare register to random value
    OCR3A = 0x12C0;

    // Enable compare match interrupt
    write_bit(1, ETIMSK, OCIE3A);
}

#include "encoder.h"
#include "node_setup.h"
#include <avr/io.h>
#include <util/delay.h>

#define SEL     PH3
#define NOT_OE  PH5
#define NOT_RST PH6


void encoder_init(){
    set_bit(DDRH, SEL);
    set_bit(DDRH, NOT_OE);
    set_bit(DDRH, NOT_RST);

    DDRK &= 0; //Set all ports in K-register to read

    _delay_ms(20);
}

int16_t encoder_read(){
    uint8_t high_byte, low_byte;

    write_bit(0, PORTH, NOT_OE);
    write_bit(0, PORTH, SEL);


    _delay_us(20);

    high_byte = PINK;
    write_bit(1, PORTH, SEL);

    _delay_us(20);

    low_byte = PINK;

    write_bit(0, PORTH, NOT_RST);
    write_bit(1, PORTH, NOT_OE);
    write_bit(1, PORTH, NOT_RST);

    return - (high_byte << 8) + low_byte;
}

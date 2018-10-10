#include "adc.h"
#include "node_setup.h"
#include <util/delay.h>
#include <avr/io.h>

volatile char *ext_adc = (char *) 0x1400;

void adc_init(void){
    DDRB &= ~(1 << PB2); //set pin PB2 to input to be used as interrupt for ADC
    //PORTB1 |= (1<< PB2); //enable internal pull-up-resistor
}

int adc_read_channel(unsigned int channel){
    ext_adc[0] = (uint8_t)(channel+3);
    //_delay_us(1);
    //while (PINB & (1<<PB2)) {
    //    _delay_us(1);
    //}
    _delay_us(60);
    volatile uint8_t readout = ext_adc[0];
    _delay_us(1);
    return readout;
}

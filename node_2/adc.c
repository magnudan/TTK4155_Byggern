#include "node_setup.h"
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

void adc_init(){
    //set reference to internal 2.4v
    set_bit(ADMUX, REFS1);
    set_bit(ADMUX, REFS0);
    
    //enable auto-trigger of the adc
    set_bit(ADCSRA, ADATE);

    //enable adc
    set_bit(ADCSRA, ADEN);

    //set clock prescaler to 1/128
    set_bit(ADCSRA, ADPS2);
    set_bit(ADCSRA, ADPS1);
    set_bit(ADCSRA, ADPS0);

    //start the first adc cycle
    set_bit(ADCSRA, ADSC);
}

uint16_t adc_read(){
    return ADC;
}

#include "adc.h"
#include "node_setup.h"
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

void adc_init(){
    //set reference to internal 2.4v
    write_bit(1, ADMUX, REFS1);
    write_bit(1, ADMUX, REFS0);

    //enable auto-trigger of the adc
    write_bit(1, ADCSRA, ADATE);

    //enable adc
    write_bit(1, ADCSRA, ADEN);

    //set clock prescaler to 1/128
    write_bit(1, ADCSRA, ADPS2);
    write_bit(1, ADCSRA, ADPS1);
    write_bit(1, ADCSRA, ADPS0);

    //start the first adc cycle
    write_bit(1, ADCSRA, ADSC);

    //Read input from AD0
    write_bit(0, ADMUX, MUX0);
    write_bit(0, ADMUX, MUX1);
    write_bit(0, ADMUX, MUX2);
    write_bit(0, ADMUX, MUX3);
    write_bit(0, ADMUX, MUX4);
    printf("ADC initialized\r\n");
}

uint16_t adc_read(){
    return ADC;
}

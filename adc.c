#include "adc.h"
#include <util/delay.h>

volatile char *ext_adc = (char *) 0x1400;

int adc_read_channel(unsigned int channel){
    ext_adc[0] = (uint8_t)(channel+3);
    _delay_us(1);
    volatile uint8_t readout = ext_adc[0];
    _delay_us(1);
    return readout;
}

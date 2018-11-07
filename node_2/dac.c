#include "node_setup.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include "dac.h"
#include <util/delay.h>

#define DAC_ADDRESS     0b01011110
#define DAC_PIN_SELECT  0b00000000
#define DAC_ADDRESS_BYTE 0
#define DAC_COMMAND_BYTE 1
#define DAC_OUTPUT_BYTE  2

void DAC_init(){
    TWI_Master_Initialise();
    set_bit(PORTD, PD2);
    set_bit(PORTD, PD1);
}


void DAC_send(uint8_t value){
    char msgSize = 3;
    char msg[3];
    msg[DAC_ADDRESS_BYTE] = DAC_ADDRESS;
    msg[DAC_COMMAND_BYTE] = DAC_PIN_SELECT;
    msg[DAC_OUTPUT_BYTE]  = value;
    TWI_Start_Transceiver_With_Data(msg, msgSize);
    _delay_us(50);
}

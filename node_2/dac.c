#include "node_setup.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include "dac.h"
#include <util/delay.h>

void DAC_init(){
    TWI_Master_Initialise();
}


void DAC_send(uint8_t value){
    char msgSize = 3;
    char msg[3];
    msg[DAC_ADDRESS_BYTE] = DAC_ADDRESS;
    msg[DAC_COMMAND_BYTE] = DAC_PIN_SELECT;
    msg[DAC_OUTPUT_BYTE] = value;
    TWI_Start_Transceiver_With_Data(msg, msgSize);
    _delay_us(50);
}

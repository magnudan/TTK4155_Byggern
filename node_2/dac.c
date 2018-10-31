#include "node_setup.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include "dac.h"
#include <util/delay.h>

void DAC_init(){


    TWI_Master_Initialise();
    //set_bit(DDRD, PD0);
    //set_bit(DDRD, PD1);
    //set_bit(TWCR, TWIE);
	//set_bit(PORTD, PD0); //SCL port
    //set_bit(PORTD, PD1); //SDA port

}


void DAC_send(uint8_t value){
    char msgSize = 3;
    char msg[3];
    msg[DAC_ADDRESS_BYTE] = DAC_ADDRESS;
    msg[DAC_COMMAND_BYTE] = DAC_PIN_SELECT;
    msg[DAC_OUTPUT_BYTE] = value;
    TWI_Start_Transceiver_With_Data(msg, msgSize);
    _delay_us(50);
    //TWCR = (0<<TWIE);
/*
    unsigned char msgSize = 3;
	unsigned char* i2c_write = malloc(3*sizeof(char));

	i2c_write[0] = dac_adress;
	i2c_write[1] = 0x00;
	i2c_write[2] = (uint8_t) value;
	_delay_us(50);

	TWI_Start_Transceiver_With_Data(i2c_write, msgSize);
    free(i2c_write);*/
}

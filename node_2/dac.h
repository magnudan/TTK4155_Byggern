#include <avr/io.h>

void DAC_init();
void DAC_send(uint8_t message);


#define DAC_ADDRESS     0b01011110
#define DAC_PIN_SELECT  0b00000000
#define DAC_ADDRESS_BYTE 0
#define DAC_COMMAND_BYTE 1
#define DAC_OUTPUT_BYTE  2

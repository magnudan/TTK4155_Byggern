// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "cpu_info.h"

#include <avr/io.h>
#include <util/delay.h>
int main(void){
    // Buttons input (the whole port)
    DDRC = 0xFF;
    while(1){
        PORTC = 0xFF;
        _delay_ms(100);
        PORTC = 0x00;
        _delay_ms(100);
    }
}

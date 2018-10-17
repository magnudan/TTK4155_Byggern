#define F_CPU 16000000UL
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/io.h>

void main(){
    uart_init();
    DDRF |= (1<<PF0);
    while(1){
        _delay_ms(5);
        printf("hello\r\n");
    }
}

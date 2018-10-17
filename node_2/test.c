#include "node_setup.h"
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/io.h>

void main(){
    uart_init();
    DDRF |= (1<<PF0);
    while(1){
        _delay_ms(20);
        printf("Henlo\r\n");
        PORTF |= (1<<PF0);
        _delay_ms(1000);
        printf("Zoooop Loop\r\n");
        PORTF &= ~(1<<PF0);
    }
}

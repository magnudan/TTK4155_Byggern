#include "utils.h"
#include "uart.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void main()
{
    uart_init();
    timer_init();
    sei();
    while(1){
        printf("henlo\r\n");
        _delay_ms(500);
    }
}


ISR(TIMER1_COMPA_vect)
{
    printf("zoop loop\r\n");
}

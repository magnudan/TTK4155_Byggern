#include "cpu_info.h"
#include <avr/io.h>
#include <stdint.h>
#define BAUD 9600
#define BAUDRATE ( (F_CPU) / (BAUD * 16UL) - 1 )

void uart_init(){
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = BAUDRATE;
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C |= (1 << URSEL0) | (1 << UCSZ00) | (1 << UCSZ01); // Trasmit size 8 bit
}

void uart_transmit(uint8_t data){
    while (!( UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

uint8_t uart_recieve(void){
    while(!(UCSR0A) & (1 << RXC0));
    return UDR0;
}

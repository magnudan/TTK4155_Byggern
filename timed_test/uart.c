#include "uart.h"

#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include "utils.h"

#define BAUD 9600 
#define BAUDRATE ( (F_CPU) / (BAUD * 16UL) - 1 )
FILE* uart;

void uart_init(){
    UBRR0H = (BAUDRATE >> 8);       // set high register of the baud rate register UBRR0
    UBRR0L = BAUDRATE;              // set low register of the baud rate register UBRR0
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01) | (1<<USBS0); // Trasmit size 8 bit - 2 stop bits
    uart_enable();
    uart = fdevopen(&uart_transmit, &uart_receive);
}

int uart_transmit(char data, FILE *f){
    while (!( UCSR0A & (1 << UDRE0)));      //wait for empty data register UDR0
    UDR0 = data;
    return 0;
}

int uart_receive(FILE* f){
    return 0;
}

void uart_enable(){
    bit_write(1, UCSR0B, TXEN0);    //enable transmit 
}


void uart_disable(){
    bit_write(0, UCSR0B, TXEN0);    //disable transmit 
}

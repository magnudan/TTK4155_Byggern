#include "node_setup.h"
#include "uart_driver.h"
#include <avr/io.h>
#include <stdint.h>

#define BAUD 9600
#define BAUDRATE ( (F_CPU) / (BAUD * 16UL) - 1 )
FILE *uart;

void uart_init(){
    UBRR0H = (BAUDRATE >> 8);       // set high register of the baud rate register UBRR0
    UBRR0L = BAUDRATE;              // set low register of the baud rate register UBRR0
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);      //enable transmit and recieve
    UCSR0C |= (3 << UCSZ00) | (1<<USBS0); // Trasmit size 8 bit - 2 stop bits

    uart = fdevopen(&uart_transmit, &uart_recieve);
    printf("UART initialized\r\n");
}

int uart_transmit(char data, FILE *f){
    while (!( UCSR0A & (1 << UDRE0)));      //wait for empty data register UDR0
    UDR0 = data;
    return 0;                      //fill UDR0 with data
}

int uart_recieve(FILE *f){
    while(!(UCSR0A) & (1 << RXC0));         //wait for empty data register UDR0
    return UDR0;                            //fetch UDR0 data
}

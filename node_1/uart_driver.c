// Header include
#include "uart_driver.h"
#include "node_setup.h"


// Library includes
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>


// Globals define
FILE *uart;


void uart_init()
{
    // Set the high and low baudrate registers to reflect the BAUD defined
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = BAUDRATE;
    //UBRR0H = 0x00;
    //UBRR0L = 0x55;  // 0x1F = 31


    // Set transmission size to 8 bits

    //write_bit(1, UCSR0C, URSEL0);
    //write_bit(1, UCSR0C, UCSZ00);
    //write_bit(1, UCSR0C, UCSZ01);

    // Set stop bits to 2 bits
    //write_bit(1, UCSR0C, USBS0);
    UCSR0C |= (1 << URSEL0) | (1 << USBS0) | (1 << UCSZ00)| (1 << UCSZ01);
    // Enable transmit and recieve
    write_bit(1, UCSR0B, TXEN0);
    write_bit(1, UCSR0B, RXEN0);


    // Open a stream to use fprint function
    uart = fdevopen(&uart_transmit, &uart_recieve);
}


int uart_transmit(char data, FILE *f)
{
    //wait for empty data register UDR0
    while (!(test_bit(UCSR0A, UDRE0)));

    //load character data into uart send buffer
    UDR0 = data;
    return 0;
}


int uart_recieve(FILE *f)
{
    //wait for data recieved flag
    while(!(test_bit(UCSR0A, RXC0)));

    //fetch UDR0 data
    return UDR0;
}

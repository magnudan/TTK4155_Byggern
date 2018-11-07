#ifndef uart_driver_H_
#define uart_driver_H_
#include <stdio.h>
#endif

#define BAUD 9600
#define BAUDRATE ( (F_CPU) / (BAUD * 16UL) - 1 )

extern FILE *uart;

void uart_init (void);
int uart_transmit (char data, FILE *f);
int uart_recieve (FILE *f);

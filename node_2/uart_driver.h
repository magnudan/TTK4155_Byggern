#ifndef uart_driver_H_
#define uart_driver_H_

#include <stdio.h>

void uart_init (void);

int uart_transmit ( char data, FILE* f);

int uart_recieve (FILE* f);

extern FILE *uart;

#endif

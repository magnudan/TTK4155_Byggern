#ifndef uart_driver_H_
#define uart_driver_H_

#include <stdio.h>

#endif

void uart_init (void);

int uart_transmit (char data, FILE *f);

unsigned char uart_recieve (void);

extern FILE *uart;

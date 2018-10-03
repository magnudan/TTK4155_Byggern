#include <avr/io.h>


void SPI_init();

void SPI_select_slave(void);

void SPI_deselect_slave(void);

void SPI_transmit_byte(char data_byte);

char SPI_recieve_byte(void);

void SPI_test_loop(void);

#ifndef spi_H_
#define spi_H_

#include <avr/io.h>

#endif

void SPI_init();
void SPI_select_slave();
void SPI_deselect_slave();
void SPI_transmit_byte(uint8_t data_byte);
uint8_t SPI_recieve_byte();
void SPI_test_loop();

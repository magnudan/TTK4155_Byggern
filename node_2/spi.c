#include <avr/io.h>
#include "node_setup.h"
#include <util/delay.h>
#include "spi.h"

//Define SPI pins

#define SPI_PORT_DDR DDRB
#define SPI_PORT PORTB
#define SPI_SS PB7
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SCK PB1
#define IO_BOARD_SS PB0

void SPI_init(void) {
	//Set MOSI, SCK and SS as output pins
	SPI_PORT_DDR |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS) | (1<<IO_BOARD_SS);

	//Set MISO as input pin
	SPI_PORT_DDR &= ~(1<<SPI_MISO);

	//Enable SPI in master mode and set clock rate fosc/16
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
		//| (1 << SPR1)
}

void SPI_transmit_byte(uint8_t data_byte) {
	//Start the transmission
	SPDR = data_byte;

	//Wait for data to be transmitted (checks if the register is empty)
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_recieve_byte(void) {
	//Send dummy data to read from slave
	SPI_transmit_byte(0);
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));

	return SPDR;
}

void SPI_select(void) {
	//Set !SS to 0 to select the slave
	SPI_PORT &= ~(1<<SPI_SS);
	//SPI_PORT &= ~(1<<PB7);
}

void SPI_deselect(void) {
	//Set !SS to 1 to deselect the slave
	SPI_PORT |= (1<<SPI_SS);
	//SPI_PORT |= (1<<PB7);
}

void SPI_test_loop(void){
	SPI_init();
	int i = 0;
	while(1){
		i++;
		SPI_select();
		SPI_transmit_byte(0x50);
		SPI_deselect();
		_delay_ms(1);
	}
}

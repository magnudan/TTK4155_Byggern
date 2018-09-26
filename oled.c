#include "oled.h"
#include <avr/io.h>
#include <stdio.h>
#include "uart_driver.h"
#include "fonts.h"

volatile char *ext_oledc = (char *) OLEDC_START_ADDR;
volatile char *ext_oledd = (char *) OLEDD_START_ADDR;

uint8_t page, col;

void oled_init(){



    *ext_oledc = 0xAE; // display off
    *ext_oledc = 0xA1; // segment remap
    *ext_oledc = 0xDA; // common pads hardware alternative
    *ext_oledc = 0x12;
    *ext_oledc = 0xC8; // common output scan direction com63-com0
    *ext_oledc = 0xA8; // mulitplex ration mode: 63
    *ext_oledc = 0x3F;
    *ext_oledc = 0xD5; // display divide ration/osc.freq. mode
    *ext_oledc = 0x80;
    *ext_oledc = 0x81; // contrast control
    *ext_oledc = 0x50;
    *ext_oledc = 0xD9; // set pre-charge period
    *ext_oledc = 0x21;
    *ext_oledc = 0x20; // set memory adressing mode
    *ext_oledc = 0x02;
    *ext_oledc = 0xDB; // VCOM deselect level mode
    *ext_oledc = 0x30;
    *ext_oledc = 0xAD; // master configuration
    *ext_oledc = 0x00;
    *ext_oledc = 0xA4; // out follows RAM content
    *ext_oledc = 0xA6; // set normal display
    *ext_oledc = 0xAF; // display on

	*ext_oledc = 0xB0; // Set page start address, command B0-B7, B0: page 0, B1: page 1 ...
    *ext_oledc = 0x00; //Set lower column start address
    *ext_oledc = 0x10; //Set higher column start address*/

    oled_home();
}

void oled_home(){
    page = 0;
    col = 0;
    *ext_oledc = 0x21; //Setup column start and end address
    *ext_oledc = 0x00;
    *ext_oledc = 0x7F;

    *ext_oledc = 0x22; //Setup page start and end address
    *ext_oledc = 0x0;
    *ext_oledc = 0x7;
}


void oled_goto_line(uint8_t line){
    if(line > 7){
        printf("Error: line bigger than 7.\n\r");
    }
    else {
        oled_home();
        page = line;
        *ext_oledc = 0xB0 + line;
        //*ext_oledc = 0x00;
        //*ext_oledc = 0x10;
    }
}

void oled_goto_column(uint8_t column){
    if(column > 127){
        printf("Error: column bigger than 127.\n\r");
    }
    else{
        col = column;
        *ext_oledc = 0x21;
        *ext_oledc = 0x00 + column;
        *ext_oledc = 0x7F;
    }
}

void oled_clear_line(uint8_t line){
    oled_goto_line(line);
    for(uint8_t i = 0; i < 128; i++){
        ext_oledd[i] = 0x00;
    }
}

void oled_pos(uint8_t row,uint8_t column){
    oled_goto_line(row);
    oled_goto_column(column);
}


void oled_print_char(char c){
    for(int i = 0; i < 8; i++){
        *ext_oledd =  pgm_read_byte(&font8[c][i]);
        oled_goto_column(col + 1);
    }
}

void oled_print_char_negative(char c){
    for(int i = 0; i < 8; i++){
        *ext_oledd =  pgm_read_byte(&font8[c][i]);
        oled_goto_column(col + 1);
    }
}

void oled_print_string(char cstring[]){
    int i = 0;
    while(cstring[i] != '\0'){
        oled_print_char(cstring[i] - ' ');
        i++;
    }
}

void oled_print_string_negative(char cstring[]){
    int i = 0;
    while(cstring[i] != '\0'){
        oled_print_char_negative(cstring[i] - ' ');
        i++;
    }
}

void oled_clear_all()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        *ext_oledc = 0xB0 + i;
        for(uint32_t i = 0; i<128; i++)
        {
            ext_oledd[i] = 0x00;
        }
    }
}

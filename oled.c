#include "oled.h"

volatile char *ext_oledc = (char *) OLEDC_START_ADDR;
volatile char *ext_oledd = (char *) OLEDD_START_ADDR;

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


}

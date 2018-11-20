#include "java.h"
#include "node_setup.h"
#include "oled.h"
#include <avr/io.h>
#include <util/delay.h>

#define COFFEE_PIN PD3

void java_init(){
    write_bit(1, DDRD, COFFEE_PIN); //Set data direction to output
    write_bit(1, PORTD, COFFEE_PIN);
}

void java_make(){
    write_bit(0, PORTD, COFFEE_PIN);
    oled_home();
    oled_clear_display();
    oled_write_line("Brewing coffee");
    _delay_ms(1000);
}

void java_stop(){
    write_bit(1, PORTD, COFFEE_PIN);
    oled_home();
    oled_clear_display();
    oled_write_line("Shutting down");
    _delay_ms(1000);
}

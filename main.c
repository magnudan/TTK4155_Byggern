// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "cpu_info.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include "button.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void testFunction_1(){
    volatile char readout[] = " ";
    printf("X: ");
    printf("%d", adc_read_channel(JOYSTICK_X));
    printf("\tY: ");
    printf("%d", adc_read_channel(JOYSTICK_Y));
    printf("\tSlider L: ");
    printf("%d", adc_read_channel(SLIDER_L));
    printf("\tSlider R: ");
    printf("%d", adc_read_channel(SLIDER_R));
    printf("\tButton L: ");
    printf("%d", button_read(BUTTON_L));
    printf("\tButton R: ");
    printf("%d", button_read(BUTTON_R));
    printf("\n\r");
    _delay_ms(200);
    _delay_us(30);
}

void testFunction_2(){
    //oled_clear_all();
    _delay_ms(100);
    oled_pos(0, 0);
    char test[] = "Hello, laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaang tekst!";
    //oled_print_string(test);
    oled_print_string_SRAM(test);
    //oled_print_string((char)(button_read(BUTTON_JOYSTICK)));
    _delay_ms(500);
    //oled_print_string_SRAM("DETTTE");
    _delay_ms(1000);
}

void testFunction_3(){
    oled_refresh_display();
    _delay_ms(1000);
    oled_write('X', 50,5);
    _delay_ms(1000);
    oled_refresh_display();
    oled_write('O', 50,5);
}

void timer_interupt_init()
{
    TCCR0 = 0x00;
    TCCR0 = (1<<CS02) | (1<<CS00); //set timer prescaler to 1024
    TIMSK = (1<<TOIE0); //enable timer0 overflow interrupt
    //OCR0 = 80;
    sei();
}



int main(void){

    volatile char *ext_oledc = (char *) OLEDC_START_ADDR;
    volatile char *ext_oledd = (char *) OLEDD_START_ADDR;


    uart_init();
    SRAM_init();
    SRAM_test();
    adc_init();
    button_init();
    oled_init();
    //timer_interupt_init();
    oled_clear_all_SRAM();
    init_menu();
    printf("henlo");
    SPI_test_loop();
}

ISR(TIMER0_OVF_vect)    //interrupt routine to update oled-display at fixed intervals
{
    //oled_refresh_display();
}

// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "cpu_info.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include "button.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

volatile char *ext_oledc = (char *) 0x1000;
volatile char *ext_oledd = (char *) 0x1200;
volatile char *ext_sram = (char *) 0x1800;

int main(void){
    uart_init();
    SRAM_init();
    SRAM_test();
    adc_init();
    button_init();
    while (1) {
        *ext_oledc = 0xFF;
        _delay_us(30);
        *ext_oledc = 0x00;
        _delay_us(30);
        *ext_sram = 0xFF;
        _delay_us(30);
        *ext_oledd = 0xFF;
        _delay_us(30);
        *ext_oledd = 0x00;
        _delay_us(30);

        /*
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
        */
    }
}

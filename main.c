// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "cpu_info.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include "button.h"
#include "oled.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


int main(void){

    volatile char *ext_oledc = (char *) OLEDC_START_ADDR;
    volatile char *ext_oledd = (char *) OLEDD_START_ADDR;

    uart_init();
    SRAM_init();
    SRAM_test();
    adc_init();
    button_init();
    oled_init();
    while (1) {

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
        _delay_us(30);
        */

        for (uint8_t i = 0; i < 8; i++) {
            *ext_oledc = 0xB0 + i;
            for(uint32_t i = 0; i<128; i++){
                ext_oledd[i] = 0x00;
            }
        }
        _delay_ms(100);
        oled_goto_line(3);
        oled_goto_column(0);
        char test[] = "Hello world!";
        oled_print_string(test);
        oled_goto_column(0);
        _delay_ms(2000);
    }


}

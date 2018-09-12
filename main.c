// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "cpu_info.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void){
    uart_init();
    SRAM_init();
    SRAM_test();
    while (1) {
        volatile char readout[] = " ";
        printf("X: ");
        printf("%d", adc_read_channel(JOYSTICK_X));
        printf("\tY: ");
        printf("%d", adc_read_channel(JOYSTICK_Y));
        printf("\tSlider L: ");
        printf("%d", adc_read_channel(SLIDER_L));
        printf("\tSlider R: ");
        printf("%d", adc_read_channel(SLIDER_R));
        printf("\n\r");
        _delay_ms(200);
    }
}

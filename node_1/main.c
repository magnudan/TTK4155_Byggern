// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "node_setup.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include "button.h"
#include "oled.h"
//#include "menu.h"
#include "menu_2_0.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "joystick_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include <stdlib.h>

void print_multifunction_card(){
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
    printf("\tButton Joystick: ");
    printf("%d", button_read(BUTTON_JOYSTICK));
    printf("\n\r");
}

void testFunction_2(){
    _delay_ms(100);
    oled_home();
    char test[] = "Hello, laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaang tekst!\0";
    oled_print_string_SRAM(test);
}

void testFunction_3(){
    oled_refresh_display();
    _delay_ms(1000);
    oled_write('X', 50,5);
    _delay_ms(1000);
    oled_refresh_display();
    oled_write('O', 50,5);
}



int main(void){

    volatile char *ext_oledc = (char *) OLEDC_START_ADDR;
    volatile char *ext_oledd = (char *) OLEDD_START_ADDR;
    volatile char *ext_test = (char *) 0x0000;

    write_bit(1, DDRE, PE2);

    uart_init();
    /*
    SRAM_init();
    SRAM_test();
    adc_init();
    button_init();
    oled_init();
    timer_init();
    SPI_init();
    MCP_init();
    CAN_init();
    oled_clear_all_SRAM();
    menu_init();
*/

    while(1){
        //joystick_send();
        //touch_send();
        //menu_loop();

        printf("%c", 0x55);

        //testFunction_2();
        //Can_block recieved_can_block = CAN_recieve(1);
        //printf("Can: %d\r\n", recieved_can_block.data[1]);

        write_bit(1, PORTE, PE2);
        _delay_ms(500);
        write_bit(0, PORTE, PE2);
        _delay_ms(500);
    }

}


ISR(TIMER1_COMPA_vect)    //interrupt routine to update oled-display at fixed intervals
{
    oled_refresh_display();
    TCNT1 = 0x00;
}


ISR(INT0_vect){
    Can_block my_other_can_block = CAN_recieve(1);
    oled_clear_all_SRAM();
    oled_print_string_SRAM("Score is: ");
    oled_print_string_SRAM(utoa(my_other_can_block.data[0], 6, 10));

}

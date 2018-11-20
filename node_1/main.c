#include "node_setup.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include "button.h"
#include "oled.h"
#include "menu_2_0.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "joystick_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include <util/delay.h>
#include "pwm.h"
#include "game.h"
/*
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
    oled_write_string(test);
}

void testFunction_3(){
    oled_refresh_display();
    _delay_ms(1000);
    oled_write_char('X', 50,5);
    _delay_ms(1000);
    oled_refresh_display();
    oled_write_char('O', 50,5);
}


*/
int main(void){

    //volatile char *ext_oledc = (char *) OLEDC_START_ADDR;
    //volatile char *ext_oledd = (char *) OLEDD_START_ADDR;
    //volatile char *ext_test = (char *) 0x0000;
    //cli();

    uart_init();
    pwm_init();
    SRAM_init();
    SRAM_test();
    adc_init();
    button_init();
    oled_init();
    timer_init();
    SPI_init();
    MCP_init();
    CAN_init();
    menu_init();
    sei();
    oled_clear_display();
    game_timer_init();

    while(1){
        //joystick_send();
        //touch_send();
        menu_loop();
        //_delay_ms(500);

    }

}


ISR(TIMER1_COMPA_vect)    //interrupt routine to update oled-display at fixed intervals
{
    oled_refresh_display();
    TCNT1 = 0x00;
}

ISR(INT0_vect){ //Interrupt routine to update number of "fails" in
                //the game recieved by CAN from node 2
    Can_block recieved_can_block = CAN_recieve(1);
    if (recieved_can_block.data[0] == 1){
        game_increment_fails();
    }
}

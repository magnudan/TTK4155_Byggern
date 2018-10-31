// POLLING EXAMPLE(ATmega162)
// 8 buttons connected to PORTA, 8 leds to PORTB
#include "node_setup.h"
#include "sram.h"
#include "uart_driver.h"
#include "adc.h"
#include "button.h"
#include "oled.h"
#include "menu.h"
#include "spi.h"
#include "MCP2515.h"
#include "can.h"
#include "joystick_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


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
    _delay_ms(200);
    _delay_us(30);
}

void testFunction_2(){
    //oled_clear_all();
    _delay_ms(100);
    oled_pos(0, 0);
    char test[] = "Hello, laaaaaaaaaaaaaaaaaaaaaaaaaaaaaaang tekst!\0";
    //oled_print_string(test);
    oled_print_string_SRAM(test);
    //oled_print_string((char)(button_read(BUTTON_JOYSTICK)));
    _delay_ms(500);
    //oled_print_string_SRAM("DETTTE");
    oled_refresh_display();
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
    volatile char *ext_test = (char *) 0x0000;

    uart_init();
    SRAM_init();
    SRAM_test();
    adc_init();
    button_init();
    oled_init();
    //timer_interupt_init();
    oled_clear_all_SRAM();
    init_menu();
    SPI_init();
    MCP_init();
    CAN_init();
    //SPI_test_loop();
    /*uint64_t data = 0xFF00FF00FF00FF00;
    MCP_send_single_data_byte(MCP_TXB0CTRL, 3);
    MCP_load_TX_buffer(data);*/
    Can_block my_can_block = {1, 3, { 0xFF, 0xAA, 0x00}};
    CAN_reset_interrupt_flag();
    while(1){

        print_multifunction_card();
        //printf("%d\n", CAN_send(&my_can_block));
        //CAN_reset_interrupt_flag();
        //CAN_reset_interrupt_flag();
        joystick_send();
        //CAN_send(&my_can_block);

        //CAN_reset_interrupt_flag();
          //testFunction_2();
          //printf("%d\n", MCP_read_single_data_byte(MCP_CANINTF));
          //printf("%d\n", MCP_read_single_data_byte(0x2C));
          /*_delay_ms(300);
          //printf("%d\n", MCP_read_single_data_byte(0x2C));
          Can_block my_other_can_block = CAN_recieve(1);
          //printf("%0x16d\r\n", my_other_can_block.length);
          for(int i = 0; i < my_other_can_block.length; i++){
              //printf("(%d)\r\n", my_other_can_block.data[i]);
          }*/
          //printf("test");

    }
}

/*
ISR(TIMER0_OVF_vect)    //interrupt routine to update oled-display at fixed intervals
{
    //oled_refresh_display();
}
*/

ISR(INT0_vect){
    Can_block my_other_can_block = CAN_recieve(1);
    //printf("%0x16d\r\n", my_other_can_block.length);
    for(int i = 0; i < my_other_can_block.length; i++){
        printf("(%d)\r\n", my_other_can_block.data[i]);
    }
}

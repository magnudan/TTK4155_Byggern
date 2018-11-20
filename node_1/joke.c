#include "joke.h"
#include "oled.h"
#include "button.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

//Max 7 lines per joke.
//Max 15 characters per line.

//--------------
// Joke_0
//--------------
const char PROGMEM joke_1_1[16] = "Byggern is like";
const char PROGMEM joke_1_2[16] = "being the";
const char PROGMEM joke_1_3[16] = "detective in a";
const char PROGMEM joke_1_4[16] = "crime movie";
const char PROGMEM joke_1_5[16] = "where you're";
const char PROGMEM joke_1_6[16] = "also the";
const char PROGMEM joke_1_7[16] = "murderer.";

void joke_0(){
    oled_clear_display();
    char string[16];
    strcpy(string, joke_1_1);
    oled_write_line(string);
    printf("%s\r\n", string);
    strcpy(string, joke_1_2);
    oled_write_line(string);
    printf("%s\r\n", string);
    strcpy(string, joke_1_3);
    oled_write_line(string);
    printf("%s\r\n", string);
    strcpy(string, joke_1_4);
    oled_write_line(string);
    printf("%s\r\n", string);
    strcpy(string, joke_1_5);
    oled_write_line(string);
    printf("%s\r\n", string);
    strcpy(string, joke_1_6);
    oled_write_line(string);
    printf("%s\r\n", string);
    strcpy(string, joke_1_7);
    oled_write_line(string);
    printf("%s\r\n", string);

    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}

void joke_1(){
    oled_clear_display();


    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}

void joke_2(){
    oled_clear_display();


    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}

void joke_3(){
    oled_clear_display();

    //Max 15 characters per write line.
    //Max 7 lines
    oled_write_line("No");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}

void joke_4(){
    oled_clear_display();

    //Max 15 characters per write line.
    //Max 7 lines
    oled_write_line("No");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}

void joke_5(){
    oled_clear_display();

    //Max 15 characters per write line.
    //Max 7 lines
    oled_write_line("No");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    //oled_write_line("");
    while(button_read(BUTTON_JOYSTICK)){
        _delay_ms(10);
    }
}

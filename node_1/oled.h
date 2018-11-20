#ifndef oled_H_
#define oled_H_

#include <avr/io.h>

#define OLEDC_START_ADDR 0x1000
#define OLEDD_START_ADDR 0x1200

#endif


void oled_init(void);

void oled_home(void);

void oled_goto_line(uint8_t line);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_goto_pos(uint8_t row, uint8_t column);

//void oled_print_char(char c);

//void oled_print_string(char cstring[]);


//void oled_print_char_negative(char c);

//void oled_print_string_negative(char cstring[]);

void oled_clear_display();

void oled_write_byte(unsigned int data, int col, int row);

void oled_refresh_display();

void oled_write_string(char cstring[]);

void oled_write_char(char c);

void oled_write_line(char cstring[]);

void oled_draw_line(int x0, int y0, int x1, int y1);

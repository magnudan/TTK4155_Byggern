#include <avr/io.h>


#define OLEDC_START_ADDR 0x1000
#define OLEDD_START_ADDR 0x1200

void oled_init(void);

void oled_home(void);

void oled_goto_line(uint8_t line);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_pos(uint8_t row, uint8_t column);

void oled_print_char(char c);

void oled_print_string(char cstring[]);

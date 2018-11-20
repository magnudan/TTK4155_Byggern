#ifndef fail_counter_H_
#define fail_counter_H_

#include <avr/io.h>

#endif

void fail_counter_init();
uint8_t fail_counter_get();
void fail_counter_add();
void fail_counter_reset();
void fail_counter_update();

#include "fail_counter.h"
#include "node_setup.h"
#include "adc.h"
#include "can.h"
#include <avr/io.h>

#define DIODE_CONNECTION PF0
#define DIODE_THRESHOLD 120

enum State{IDLE, UPDATING};

uint8_t fails = 0;

Can_block fail = {1, 2, {1}};

void fail_counter_init(){
    write_bit(0, DDRF, DIODE_CONNECTION);
    fails = 0;
    printf("Score counter initialized\r\n");
}

uint16_t diode_read(){
    return adc_read();
}

void fail_counter_add(){
    fails ++;
}

uint8_t fail_counter_get(){
    return fails;
}

void fail_counter_reset(){
    fails = 0;
}

void fail_counter_update(){
    static enum State state = IDLE;
    static uint8_t counter = 0;
    uint8_t diode_reading = diode_read();
    if ((state == IDLE) && (diode_reading < DIODE_THRESHOLD)){
        counter++;
        if(counter ==  3){
          state = UPDATING;
        }
    }
    else if((state == IDLE)){
      counter = 0;
    }
    else if ((state == UPDATING) && (diode_reading > DIODE_THRESHOLD)){
        fail_counter_add();
        CAN_send(&fail);
        state = IDLE;
    }
}

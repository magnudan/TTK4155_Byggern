#include "score_counter.h"
#include "node_setup.h"
#include "adc.h"
#include <avr/io.h>

#define DIODE_CONNECTION PF0
#define DIODE_THRESHOLD 120

enum State{IDLE, UPDATING};

uint8_t score = 0;

void score_counter_init(){
    write_bit(0, DDRF, DIODE_CONNECTION);
    score = 0;
    printf("Score counter initialized\r\n");
}

uint16_t diode_read(){
    return adc_read();
}

void score_counter_add(){
    score ++;
}

uint8_t score_counter_get(){
    return score;
}

void score_counter_reset(){
    score = 0;
}

void score_counter_update(){
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
        score_counter_add();
        state = IDLE;
    }
}

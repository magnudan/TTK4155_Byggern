#include "button.h"
#include "cpu_info.h"
#include <avr/io.h>

void button_init(void){
    DDRB &= ~(1 << BUTTON_L); //set pin PB0 to input
    DDRB &= ~(1 << BUTTON_R); //set pin PB1 to input
}

// accepts BUTTON_L or BUTTON_R as input
unsigned int button_read(unsigned int button){
        if (PINB & (1<<button)) {
            return 1;
        }
        return 0;
}

#include "button.h"
#include "node_setup.h"
#include <avr/io.h>

void button_init(void){
    DDRB &= ~(1 << BUTTON_L); //set pin PB0 to input
    DDRB &= ~(1 << BUTTON_R); //set pin PB1 to input
    DDRB &= ~(1 << BUTTON_JOYSTICK); //set pin PB3 to input

    //printf("Buttons initialized\r\n");
}

// accepts BUTTON_L or BUTTON_R as input
unsigned int button_read(unsigned int button){
        if ((button == BUTTON_L) || (button == BUTTON_R)){
            if (PINB & (1<<button)) {
                return 1;
            }
            return 0;
        }

        else{
            if (PINB & (1<<button)) {
                return 0;
            }
            return 1;
        }
}

#include "node_setup.h"
#include "uart_driver.h"
#include <util/delay.h>
#include <avr/io.h>
//#include <avr/interrupt.h>

void internal_adc_init();
uint16_t internal_adc_read_low();

int main(){
    uart_init();
    internal_adc_init();
    DDRF |= (1<<PF1);

    while(1){
        printf("hallo\r\n");
       _delay_ms(1000);
    }
}



void internal_adc_init(){
    //enable adc conversion (defaults to ADC0 single ended conversion)
    ADCSRA |= (1<<ADEN);
    /*set prescaler to 1/128
    ADCSRA |= (1<<ADPS2) 
            | (1<<ADPS1) 
            | (1<<ADPS0);
    ADMUX |= (1<<REFS0) 
            | (1<<REFS1);*/
}


uint16_t internal_adc_read_low(){
   ADCSRA |= (1<<ADSC);
   while (ADCSRA & (1<<ADSC)){
       //do nothinf
   }
   return ADC;
}

#ifndef adc_H_
#define adc_H_

#define SLIDER_L    4
#define SLIDER_R    5
#define JOYSTICK_Y  6
#define JOYSTICK_X  7

#endif

void adc_init(void);
int adc_read_channel(unsigned int channel);

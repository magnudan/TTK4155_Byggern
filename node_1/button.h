#ifndef button_H_
#define button_H_

#define BUTTON_L PB0
#define BUTTON_R PB1
#define BUTTON_JOYSTICK PB3

#endif

void button_init(void);
unsigned int button_read(unsigned int button_nr);

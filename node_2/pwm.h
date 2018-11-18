#ifndef pwm_H_
#define pwm_H_

#endif

void PWM_init();
void PWM_set_angle(uint8_t angle); //angle is a number between 0 and 255
void PWM_move_left(uint8_t signal);
void PWM_move_right(uint8_t signal);

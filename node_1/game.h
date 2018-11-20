#ifndef game_H_
#define game_H_

#endif

void game_reset_fails();
uint8_t game_get_fails();
void game_over();
void game_write_fails_oled();
void game_write_fails_from_menu();
void game_increment_fails();
void game_loop_position(void);
void game_loop_speed(void);
void game_loop_udp();

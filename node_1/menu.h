#ifndef menu_H_
#define menu_H_


#endif

typedef enum {UP,DOWN, RIGHT, LEFT} Menu_direction;

void print_current_menu_level();
void move_pointer_in_menu(Menu_direction d);
void menu_loop();
void init_menu();

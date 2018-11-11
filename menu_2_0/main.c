#include <stdio.h>
#include "menu.h"

void zooploop()
{
    printf("zoop loop\r\n");
}


void main()
{
    menu_print();
    menu_link_to_function(&top, 1, zooploop);
    menu_down();
    menu_enter();
}

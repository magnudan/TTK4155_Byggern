#include "menu.h"
#include <stdio.h>



//--------------------------------------------
// Menu globals and accessory functions
//--------------------------------------------
Menu*   current_menu = &top;

Menu_item* get_current_menu_item()
{
    return &(current_menu->menu_items[current_menu->current_menu_item]); 
}



//--------------------------------------------
// Menu functions
//--------------------------------------------
void menu_enter()
{
    Menu_item* curr = get_current_menu_item();
    if(curr -> function == NULL)
    {
        current_menu = curr -> child_menu;
    }
    else
    {
        curr -> function();
    }
}


void menu_return()
{
    if(current_menu -> parent_menu != NULL)
    {
        current_menu = current_menu -> parent_menu;
    }
}


void menu_up()
{
    if(current_menu -> current_menu_item > 0)
    {
        (current_menu -> current_menu_item) --;
    }
}


void menu_down()
{
    if(current_menu -> current_menu_item < MAX_MENU_SIZE)
    {
        (current_menu -> current_menu_item) ++;
    }
}


void menu_print()
{
    for(int i = 0; i<MAX_MENU_SIZE; i++)
    {
        if (i == current_menu -> current_menu_item)
        {
            printf("> ");
        }
        else
        {
            printf("  ");
        }
        if (current_menu -> menu_items[i].name != NULL)
        {
            printf("%s\r\n", current_menu -> menu_items[i].name);
        }
    }
}


void menu_link_to_function(Menu* menu, int menu_item_number, void (*function)(void))
{
    menu->menu_items[menu_item_number].function = function;    
}

//--------------------------------------------
// Menu definitions
//--------------------------------------------
Menu top =
{
    "Top menu",
    NULL,
    {
        {"top menu item 1",     &submenu,   NULL},
        {"top menu item 2",     NULL,       NULL},
        {"top menu item 3",     NULL,       NULL}
    }
};


Menu submenu =
{
    "sub-menu",
    &top,
    {
        {"sub menu item 1",     NULL,       NULL},
        {"sub menu item 2",     NULL,       NULL},
        {"sub menu item 3",     NULL,       NULL}
    }
};


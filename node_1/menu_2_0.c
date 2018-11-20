#include "menu_2_0.h"
#include "oled.h"
#include <stdio.h>
#include "game.h"
#include "adc.h"
#include "button.h"
#include "java.h"
#include <avr/interrupt.h>
#include <util/delay.h>


//--------------------------------------------
// Menu globals and accessory functions
//--------------------------------------------
Menu*   current_menu = &top_menu;

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
}

void menu_run_function()
{
    Menu_item* curr = get_current_menu_item();
    if(curr -> function != NULL)
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

void menu_print_OLED()
{
    cli();
    oled_clear_display();
    for(int i = 0; i<MAX_MENU_SIZE; i++)
    {
        if (i == current_menu -> current_menu_item)
        {
            oled_write_string(">");
        }
        else
        {
            oled_write_string(" ");
        }
        if (current_menu -> menu_items[i].name != NULL)
        {
            oled_write_string(current_menu -> menu_items[i].name);
        }
        oled_goto_line(i + 1);
    }
    sei();
}



void menu_link_to_function(Menu* menu, int menu_item_number, void (*function)(void))
{
    menu->menu_items[menu_item_number].function = function;
}

void do_nothing(){
    /*
    Okay, so the reason this useless thing exists is for nodes
    that should not do anything if they are pressed.
    */
    _delay_ms(10);
}

//--------------------------------------------
// Menu definitions
//--------------------------------------------
Menu top_menu =
{
    "Top menu",
    NULL,
    {
        {"Game!",   &game_menu,     NULL},
        {"Coffee",  &coffee_menu,   NULL},
        {"Joke",    &joke_menu,     NULL},
        {NULL,   NULL,       NULL},
        {NULL,   NULL,       NULL},
        {NULL,   NULL,       NULL},
    }
};


Menu game_menu =
{
    "Game menu:",
    &top_menu,
    {
        {"Analog control",  NULL,       NULL},
        {"Digital control",             NULL,       NULL},
        {"UDP control",    NULL,       NULL},
        {NULL,    NULL,       NULL},
        {NULL,    NULL,       NULL},
        {"Last number of fails",        NULL,       NULL},
    }
};

Menu coffee_menu =
{
    "Coffee menu:",
    &top_menu,
    {
        {"Coffee on",  NULL,       NULL},
        {"Coffee off", NULL,       NULL},
        {NULL,   NULL,       NULL},
        {NULL,   NULL,       NULL},
        {NULL,   NULL,       NULL},
        {NULL,   NULL,       NULL},
    }
};

Menu joke_menu =
{
    "Joke menu:",
    &top_menu,
    {
        {"Byggern is li-",  NULL,       NULL},
        {"ke being both ",  NULL,       NULL},
        {"the detective",   NULL,       NULL},
        {"and the murd-",   NULL,       NULL},
        {"erer in a ",      NULL,       NULL},
        {"crime movie. ",   NULL,       NULL}
    }
};

// Template for sub-menus
/*
Menu sub_menu =
{
    "Sub menu:",
    &top_menu,
    {
        //{"sub menu item 1",   NULL,       NULL},
        //{"sub menu item 2",   NULL,       NULL}
        //{"sub menu item 3",   NULL,       NULL}
        //{"sub menu item 4",   NULL,       NULL}
        //{"sub menu item 5",   NULL,       NULL}
        //{"sub menu item 6",   NULL,       NULL}
    }
};
*/

void menu_init(){
    java_init();

    menu_link_to_function(&top_menu, 3, do_nothing);
    menu_link_to_function(&top_menu, 4, do_nothing);
    menu_link_to_function(&top_menu, 5, do_nothing);

    menu_link_to_function(&game_menu, 0, game_loop_position);
    menu_link_to_function(&game_menu, 1, game_loop_speed);
    menu_link_to_function(&game_menu, 2, game_loop_udp);
    menu_link_to_function(&game_menu, 3, do_nothing);
    menu_link_to_function(&game_menu, 4, do_nothing);
    menu_link_to_function(&game_menu, 5, game_write_fails_from_menu);

    menu_link_to_function(&coffee_menu, 0, java_make);
    menu_link_to_function(&coffee_menu, 1, java_stop);
    menu_link_to_function(&coffee_menu, 2, do_nothing);
    menu_link_to_function(&coffee_menu, 3, do_nothing);
    menu_link_to_function(&coffee_menu, 4, do_nothing);
    menu_link_to_function(&coffee_menu, 5, do_nothing);

    menu_link_to_function(&joke_menu, 0, do_nothing);
    menu_link_to_function(&joke_menu, 1, do_nothing);
    menu_link_to_function(&joke_menu, 2, do_nothing);
    menu_link_to_function(&joke_menu, 3, do_nothing);
    menu_link_to_function(&joke_menu, 4, do_nothing);
    menu_link_to_function(&joke_menu, 5, do_nothing);

}


void menu_loop(){
    while(1){
        menu_print_OLED();
        if (adc_read_channel(JOYSTICK_Y) < 40) {
            menu_down();
        }
        else if(adc_read_channel(JOYSTICK_Y) > 200){
            menu_up();
        }
        else if(adc_read_channel(JOYSTICK_X) < 40){
            menu_return();
        }
        else if(adc_read_channel(JOYSTICK_X) > 200){
            menu_enter();
        }
        if(button_read(BUTTON_JOYSTICK)){
            menu_run_function();
        }
        _delay_ms(150);
    }
}

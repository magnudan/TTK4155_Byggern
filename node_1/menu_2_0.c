#include "menu_2_0.h"
#include "oled.h"
#include <stdio.h>
#include "game.h"
#include "adc.h"
#include "button.h"
#include <avr/interrupt.h>


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
    oled_home();
    for(int i = 0; i<MAX_MENU_SIZE; i++)
    {
        if (i == current_menu -> current_menu_item)
        {
            oled_print_string_SRAM(">");
        }
        else
        {
            oled_print_string_SRAM(" ");
        }
        if (current_menu -> menu_items[i].name != NULL)
        {
            oled_print_string_SRAM(current_menu -> menu_items[i].name);
        }
        oled_goto_line(i + 1);
    }
}



void menu_link_to_function(Menu* menu, int menu_item_number, void (*function)(void))
{
    menu->menu_items[menu_item_number].function = function;
}

//--------------------------------------------
// Menu definitions
//--------------------------------------------
Menu top_menu =
{
    "Top menu",
    NULL,
    {
        {"Game!",               &game_menu,   NULL}
        //{"top menu item 2",     NULL,       NULL},
        //{"top menu item 3",     NULL,       NULL}
    }
};


Menu game_menu =
{
    "Game menu:",
    &top_menu,
    {
        {"With position control:",     NULL,       NULL},
        {"With speed:",     NULL,       NULL},
        //{"sub menu item 3",     NULL,       NULL}
    }
};

void menu_init(){
    menu_link_to_function(&game_menu, 0, game_loop);

}


void menu_loop(){
    while(1){
        printf("hENLo\r\n");
        cli();
        oled_clear_all_SRAM();
        menu_print_OLED();
        sei();
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
    }
}

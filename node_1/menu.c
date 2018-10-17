#include <stdio.h>
#include <util/delay.h>
#include "menu.h"
#include "oled.h"
#include "button.h"
#include "adc.h"
typedef struct Node Node;

struct Node{
	char* name;
	Node* parent;
	Node* child;
	Node* sibling_up;
	Node* sibling_down;
};

Node* current_node;

Node node0;
Node node1;
Node node2;
Node node3;

Node node01;
Node node02;

Node node0 = {"menu option 1", NULL, &node01, &node3, &node1};
Node node1 = {"menu option 2", NULL, NULL, &node0, &node2};
Node node2 = {"menu option 3", NULL, NULL, &node1, &node3};
Node node3 = {"menu option 4", NULL, NULL, &node2, &node0};

Node node01 = {"menu option 01", &node0, NULL, &node02, &node02};
Node node02 = {"menu option 02", &node0, &node0, &node01, &node01};

void init_menu(){
	current_node = &node0;
}


void print_current_menu_level()
{
	oled_clear_all_SRAM();
	Node* printing_node = current_node;
	do
	{
		if(printing_node == current_node)
		{
			oled_print_string_SRAM(">");
		}
		else
		{
			oled_print_string_SRAM(" ");
		}
		printf(printing_node->name);
		oled_write_line(printing_node->name);
		printing_node = printing_node->sibling_down;
	}
	while(printing_node != current_node);
}



void move_pointer_in_menu(Menu_direction d)
{
	Node* requested_node = current_node;
	switch(d)
	{
		case UP: requested_node = current_node->sibling_up; break;
		case DOWN: requested_node = current_node->sibling_down; break;
	  	case LEFT: requested_node = current_node->parent; break;
		case RIGHT: requested_node = current_node->child; break;
	}

	if(requested_node != NULL)
	{
		current_node = requested_node;
	}
}



void menu_loop()
{
	while(1)
	{
		if (adc_read_channel(JOYSTICK_Y) < 40) {
			move_pointer_in_menu(DOWN);
		}
		else if(adc_read_channel(JOYSTICK_Y) > 200){
			move_pointer_in_menu(UP);
		}
		else if(adc_read_channel(JOYSTICK_X) < 40){
			move_pointer_in_menu(LEFT);
		}
		else if(adc_read_channel(JOYSTICK_X) > 200){
			move_pointer_in_menu(RIGHT);
		}

		print_current_menu_level();
		/*
		if (button_read(BUTTON_L)) {
			move_pointer_in_menu(DOWN);
		}
		else if(button_read(BUTTON_R)){
			move_pointer_in_menu(UP);
		}
		else if(button_read(BUTTON_JOYSTICK)){
			move_pointer_in_menu(RIGHT);
		}
		*/
		oled_refresh_display();
		_delay_ms(200);
	}
}

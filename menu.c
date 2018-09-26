#include <stdio.h>
#include "menu.h"
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

Node node01;
Node node02;

Node node0 = {"menu option 1", NULL, &node01, &node2, &node1};
Node node1 = {"menu option 2", NULL, NULL, &node0, &node2};
Node node2 = {"menu option 3", NULL, NULL, &node1, &node0};

Node node01 = {"menu option 01", &node0, NULL, &node02, &node02};
Node node02 = {"menu option 02", &node0, NULL, &node01, &node01};

int main()
{
	current_node = &node0;
	menu_loop();
}



void print_current_menu_level()
{
	Node* printing_node = current_node;
	do
	{
		if(printing_node == current_node)
		{
			printf(">>");
		}
		printf("\t%s\n", printing_node->name);
		printing_node = printing_node->sibling_down;
	}
	while(printing_node != current_node);

        printf("\n------------------");	
}



void move_pointer_in_menu(char c)
{
	Node* requested_node = current_node;
	switch(c)
	{
		case 'i': requested_node = current_node->sibling_up; break;
		case 'k': requested_node = current_node->sibling_down; break;
	  	case 'j': requested_node = current_node->parent; break;
		case 'l': requested_node = current_node->child; break;
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
		print_current_menu_level();
		move_pointer_in_menu(getchar());
		while ((getchar()) != '\n'); // flush stream of remaining characters	
	}
}
	

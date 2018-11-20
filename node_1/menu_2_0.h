#define MAX_MENU_SIZE 6


typedef struct Menu Menu;
typedef struct Menu_item Menu_item;

struct Menu_item
{
    char*       name;
    Menu*       child_menu;
    void        (*function)(void);
};


struct Menu
{
    char*       name;
    Menu*       parent_menu;
    Menu_item   menu_items[MAX_MENU_SIZE];
    int         current_menu_item;
};

Menu top_menu;
Menu game_menu;
Menu coffee_menu;

void menu_enter();
void menu_return();
void menu_up();
void menu_down();
void menu_print();
void menu_loop();
void menu_link_to_function(Menu* menu, int menu_item_number, void (*function)(void));

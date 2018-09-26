#include <stdio.h>

typedef struct Node Node;
struct Node{
    char name[16];
    int number_of_children;
    Node* children[5];
    Node* parent;
};




int main(){
    printf("\n\rzooploop\n\r");
}

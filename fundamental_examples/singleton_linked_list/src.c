/** standard C header files */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** a typical singleton node type */
typedef struct node_s {
    uint8_t value;
    struct node_s * next_node;
} node_t;

/** a typical singleton linked list */
typedef struct {
    node_t * head;
} slist_t;


/** example's global variables */
uint8_t user_selection = 0 ;
slist_t list;


void add_node(uint8_t value){

    node_t * new_node = malloc(sizeof(node_t));
    if (new_node == NULL){
        printf("[Error], node memory allocation failed \n\r");
        return;
    }

    new_node->value = value;
    new_node->next_node = NULL;

    if (list.head == NULL){
        // empty list
        list.head = new_node;
    } else {
        // Traverse to the last node
        node_t * current_node = list.head;
        while (current_node->next_node != NULL) {
            current_node = current_node->next_node;
        }
        current_node->next_node = new_node;
    }
}

void print_list(void){
    node_t *current_node = list.head;
    while(current_node != NULL){
        uint8_t current_node_value = current_node->value;
        printf("node address:%p, node value:%d \n\r", current_node, current_node_value);
        current_node = current_node->next_node;
    }
    printf("\n\r");
}

void delete_node(void){
    node_t *new_head = list.head -> next_node;
    // remove the current head (free)
    free(list.head);

    // update the head:
    list.head = new_head;

    return;
}

int main(void){
    printf("start the singleton linked list exampl by entering the menu number \n\r");

    while (1){
        printf("1. Insert a new node \n2. Print node\n3. Delete node\n0. Exit\n");
        scanf("%hhu", &user_selection);
        switch (user_selection) {
            case 1:
                printf("Add a node value: \n\r");
                int node_value = 0;
                scanf("%d", &node_value);
                add_node(node_value);
                break;
            case 2:
                print_list();
                break;
            case 3:
                delete_node();
                break;
            case 0:
                return 0;
            default:
                printf("\nInvalid choice\n");
        }
    }

    return 0;
}
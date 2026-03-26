/** standard C headers */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// ========================================================================

typedef struct node_s {
    int value;
    struct node_s * next_node;
    struct node_s * prev_node;
} node_t;


typedef struct {
    node_t * head;
} doubly_linked_list_t;

// ========================================================================

doubly_linked_list_t linked_list;

void add_item(void){

    // memeory allocation
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node){
        printf("[Error], memory allocation failed \n\r");
        return;
    }

    int new_node_value = 0;
    printf(" enter the new item value: \n\r");
    scanf("%d", &new_node_value);

    // update the new node value:
    new_node->value = new_node_value;

    // update the linked list
    if (!linked_list.head){
        linked_list.head = new_node;
        new_node->next_node = NULL;
        new_node->prev_node = NULL;
    } else {
        node_t * current_node = linked_list.head;
        while (current_node->next_node){
            current_node = current_node -> next_node;
        }
        // adding the node:
        current_node->next_node = new_node;
        new_node->prev_node = current_node;
        new_node->next_node = NULL;
    }
}

int list_all(void){
    printf("list of items in the list: \n\r");
    int counter = 0;
    node_t * current_node = linked_list.head;

    if (!current_node){
        printf("list is empty!\n\r");
        return -1;
    }

    while (current_node != NULL){
        counter++;
        printf("(%d), item value:%d \n\r", counter, current_node->value);
        current_node = current_node -> next_node;
    }

    return counter;
}

void remove_one_item(void){
    // list all stored items first:
    int count = list_all();
    if (count < 0){
        return;
    }

    /* asking what item to remove */
    int user_input = 0;
    printf("which item to remove (starting from 1 not 0) \n\r");
    scanf("%d", &user_input);

    if (user_input == 0 || user_input > count){
        printf("invalid input try again \n\r");
        return;
    }

    node_t *current_node = linked_list.head;

    if (user_input > 1){
        for (int i=0; i<(user_input-1); i++){
            current_node = current_node -> next_node;
        }
    }

    node_t * node_before_current = current_node -> prev_node;
    node_t * node_after_current = current_node -> next_node;

    // updating the links
    // ToDo: break me into clean function calls and switch for the three cases
    //       i.e., the removing the first, the middle, and the last
    if (user_input > 1 && user_input < count){
        node_before_current->next_node = current_node->next_node;
        node_after_current->prev_node = current_node->prev_node;
    } else if (user_input == 1){
        if (node_after_current != NULL){
            node_after_current->prev_node = current_node->prev_node;
        }
        linked_list.head = node_after_current;
    } else if (user_input == count && count > 1){
        node_before_current->next_node = NULL;
    }
    

    // freeing the memory
    free(current_node);

    return;

}

// ========================================================================
int main(void){
    printf("example illustrating the doubly linked list logic \n\r");
    printf("insert your choice \n\r");

    int user_choice = 0;
    bool exit_flag = false;

    while (!exit_flag){
        printf("\n");
        printf("1. add an item to the list \n\r");
        printf("2. list all items \n\r");
        printf("3. remove an item \n\r");
        printf("4. exit \n\r");

        scanf("%d", &user_choice);

        switch (user_choice){

            case 1:
                add_item();
                break;
            
            case 2:
                list_all();
                break;

            case 3:
                remove_one_item();
                break;

            case 4:
                exit_flag = true;
                break;
        }
    }

    return 0;
}
/**
 * @brief reasoning for the solution
 * 
 * Finding the subsets can be viewed as a recursive algorithm where each recursion-context or
 * each frame of nested function calls as the search attempt to find one subset. So basically,
 * we can travel over the original set and then we would have two choices, do we want to include
 * the current set element as the subset element or not. So, basically, this is a decision tree
 * recursion problem
 * 
 */

/** including the required header files */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TOTAL_SIZE 3

uint8_t A[TOTAL_SIZE] = {1, 2, 3};
uint8_t VISITED[100] = {0};
int counter = 0;
// ==================================================================

void subset_print(int index, int size){
    // check if traversed the whole set
    // if so, print the subset
    if (index == TOTAL_SIZE){
        printf("{");
        for (int i=0; i<size; i++){
            printf(" %d ", VISITED[i]);
        }
        printf("}\n\r");
        return;
    }

    // on this recursion, the size keeps the same 
    // meaning: we do not include elements into the subset
    subset_print(index + 1, size);

    // adding the element to the visited.
    VISITED[size] = A[index];
    printf("index: %d\n\r", index);

    subset_print(index+1, size+1);
}

int main(void){

    subset_print(0,0);
    return 0;
}
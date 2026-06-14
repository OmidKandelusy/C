/** 
 * @brief a private test application to test the fifo buffer subsystem 
 * 
 * 
 *
*/
// ===================================================================
// including the required header files

/** standard C header files */
#include <stdio.h>

/** subsystem header files */
#include "ff_buff.h"
// ===================================================================
// main test routine

// define a fifo out of a static memory pool
FF_DEFINE(fifo_pool, fifo_slots, fifo, 5, 32);


int main(void){

    int ret = 0;
    ret = fifo_init(&fifo);
    if (ret <0 ){
        printf("[Error], failed to initialize the fifo, ret:%d\n\r", ret);
    }

    uint8_t i = 0;
    while (ret == 0){
        i ++;
        ret = fifo_push(&fifo, &i, sizeof(i));
    }
    printf("pushing ended, ret:%d\n\r", ret);
    ret = 0;

    uint8_t j = 0xFF;
    uint16_t len = 0;
    while (ret == 0){
        ret = fifo_pop(&fifo, &j, &len);
        if (ret == 0){
            printf("popped item value:%d\n\r", j);
        }
    }
    printf("popping finished, ret:%d\n\r", ret);

    return 0;
}
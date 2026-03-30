#include "smp.h"
#include <stdio.h>

SMP_DEFINE(my_pool, 5, 5)


int main(void){

    int ret = 0;
    printf("\n test module started \n\r");

    ret =  buffer_init(my_pool, SMP_SLOT_SIZE(my_pool), SMP_SLOT_COUNT(my_pool), SMP_BUFFER(my_pool));
    if (ret){
        printf("[Error], reason:%d \n\r", ret);
    }

    uint8_t counter = 0;
    while (ret == 0){
        counter ++;
        ret = buffer_push(SMP_BUFFER(my_pool), &counter, sizeof(counter), SMP_SLOT_SIZE(my_pool));
        if (ret == 0){
            printf("slot #%d got filled \n\r", counter-1);
        }
    }
    if (ret == SMP_BUFFER_FULL){
        printf("buffer is full\n\r");
    }

    ret = 0;
    uint8_t data_slot[SMP_SLOT_SIZE(my_pool)];
    int length = 0;
    counter = 0;
    while (ret == 0){
        counter++;
        ret = buffer_pop(SMP_BUFFER(my_pool), &data_slot[0], &length);
        if (ret == 0){
            printf("slot poped, counter:%d, data[0]:%d, len:%d\n\r", counter, data_slot[0], length);
        }
        if (ret < 0 ){
            printf("Buffer is empty \n\r");
            return ret;
        }
    }


    return 0;
}
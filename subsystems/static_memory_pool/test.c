#include "smp.h"
#include <stdio.h>



SMP_DEFINE(my_pool, 5, 5)


int main(void){

    int ret = 0;
    printf("\n test module started \n\r");

    ret =  buffer_init(my_pool, SMP_SLOT_SIZE(my_pool), SMP_SLOT_COUNT(my_pool));
    
    

    return 0;
}
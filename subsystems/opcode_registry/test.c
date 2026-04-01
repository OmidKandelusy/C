/** standard C header files */
#include <stdio.h>

/** subsystem header file */
#include "opcode_registry.h"


char opcode_a[10] = "Alpha";
char opcode_b[10] = "Beta";

int alpha_handler(void){
    printf("Alpha opcode-handler triggered\n\r");

    return 0;
}

int beta_handler(void){
    printf("Beta opcode-handler triggered\n\r");

    return 0;
}



int main(void){

    printf("a simple test for the opcode registry subsystem \n\r");
    int ret = 0;

    opcode_registry_init();

    // register two opcodes:
    ret = register_opcode(opcode_a, alpha_handler);
    if (ret){
        printf("[Error], opcode registry failed, opcode:%s, reason:%d \n\r", opcode_a, ret);
        return 0;
    }

    ret = register_opcode(opcode_b, beta_handler);
    if (ret){
        printf("[Error], opcode registry failed, opcode:%s, reason:%d \n\r", opcode_b, ret);
        return 0;
    }

    printf("succes, registered opcodes : %s and %s \n\n\r", opcode_a, opcode_b);


    // trigger opcodes:
    ret = trigger_opcode(opcode_a);
    if (ret){
        printf("[Error], opcode trigger failed, opcode:%s, reason:%d \n\r", opcode_a, ret);
        return 0;
    }

    ret = trigger_opcode(opcode_b);
    if (ret){
        printf("[Error], opcode trigger failed, opcode:%s, reason:%d \n\r", opcode_b, ret);
        return 0;
    }

    // remove one opcode:
    ret = remove_opcode(opcode_a);
    if (ret){
        printf("[Error], opcode removal failed, opcode:%s, reason:%d \n\r", opcode_a, ret);
        return 0;
    }
    ret = trigger_opcode(opcode_a);
    printf("triggering removed opcode returned: %d \n\r", ret);


    return 0;
}
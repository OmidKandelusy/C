/** standard C header files */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/** function handler type */
typedef int (* fnc_handler_t)(void);

#define MAX_CMD_STRING_LENGTH 64
#define MAX_CMD_REGISTER_SIZE 10

/** a command struct type */
typedef struct {
    char cmd[MAX_CMD_STRING_LENGTH];
    fnc_handler_t cmd_handler;
} command_t;

// ============================================================

static command_t cmd_reg[MAX_CMD_REGISTER_SIZE];

int cmd_start(void){
    printf("[CMD] starting the routine \n\r");
    return 0;
}

int cmd_stop(void){
    printf("[CMD] stopping the routine \n\r");
    return 0;
}

// ============================================================
// main routine

int main(void){
    strcpy(cmd_reg[0].cmd, "START_ROUTINE");
    cmd_reg[0].cmd_handler = cmd_start;

    strcpy(cmd_reg[1].cmd, "STOP_ROUTINE");
    cmd_reg[1].cmd_handler = cmd_stop;

    char user_choice[MAX_CMD_STRING_LENGTH] = "NONE";
    int user_choice_index = 0xFF;
    int exit_condition = 0;
    while (!exit_condition){

        printf("insert your choice \n\r");
        printf("start\n\r");
        printf("stope\n\r");
        printf("exit\n\r");

        scanf("%s", &user_choice[0]);

        if (strcmp(user_choice, "start") == 0){
            user_choice_index = 1;
        } else if (strcmp(user_choice, "stop") == 0){
            user_choice_index = 2;
        } else if (strcmp(user_choice, "exit") == 0){
            user_choice_index = 3;
        } else {
            printf("[WARN] invalid input \n\r");
            user_choice_index = 0xFF;
        }

        switch (user_choice_index){
            case 3:
                exit_condition = 1;
                break;

            case 1:
                cmd_reg[0].cmd_handler();
                break;

            case 2:
                cmd_reg[1].cmd_handler();
                break;

            default:
            break;
        }

    }
}


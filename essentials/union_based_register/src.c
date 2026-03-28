/* standard C header files */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// =====================================================
// definitions and macros

/** type defintion of a 8-bit register type */
typedef union {
    uint8_t slot;

    struct {
        uint8_t enable : 1; // 1 bit
        uint8_t mode   : 2; // 2 bits
        uint8_t error  : 1; // 1 bit
        uint8_t ready  : 1; // 1 bit
        uint8_t unused : 3; // 3 bits
    } bits;
} reg8_t;

reg8_t test_reg = {0};

// =====================================================
// helper functions

void set_raw_to_register(void){
    int ret = 0;
    int val = 0;
    printf("Enter raw value (0-255) to set onto the register \n\r");

    ret = scanf("%d", &val);
    if (ret != 1){
        printf("[Error], invalid raw value \n\r");
        return;
    }

    test_reg.slot = val;
    printf("test register content:%d \n\r", test_reg.slot);

    return;
}

void set_flag(void){
    int ret = 0;
    int val = 0;
    int flg = 0;

    printf("select flag to set \n\r");
    printf(" 0. enale \n\r");
    printf(" 1. mode  \n\r");
    printf(" 2. error \n\r");
    printf(" 3. ready \n\r");

    ret = scanf("%d", &flg);
    if (ret != 1){
        printf("[Error], flag input failed \n\r");
        return;
    }
    if (flg <0 || flg > 3){
        printf("[Error], invalid flag index \n\r");
    }

    switch (flg){
        case 0:
            printf("set enable, enter 0 or 1 \n\r");
            ret = scanf("%d", &val);
            if (ret != 1){
                printf("flag value set failed \n\r");
                return;
            }
            if (val != 0 && val != 1){
                printf("flag should be either 0 or 1");
                return;
            }

            test_reg.bits.enable = val;
            break;

        case 1:
            printf("set mode value (0-3): \n\r");
            ret = scanf("%d", &val);
            if (ret !=1 ){
                printf("[Error], flag value set failed \n\r");
                return;
            }
            if (val !=0 && val !=1 && val !=2 && val !=3){
                printf("[Error], flag should be between 0 to 3 \n\r");
                return;
            }
            test_reg.bits.mode = val;
            break;

        case 2:
            printf("set error flag, enter 0 or 1 \n\r");
            ret = scanf("%d", &val);
            if (ret != 1){
                printf("flag value set failed \n\r");
                return;
            }
            if (val != 0 && val != 1){
                printf("flag should be either 0 or 1");
                return;
            }

            test_reg.bits.error = val;
            break;

        case 3:
            printf("set ready flag, enter 0 or 1 \n\r");
            ret = scanf("%d", &val);
            if (ret != 1){
                printf("flag value set failed \n\r");
                return;
            }
            if (val != 0 && val != 1){
                printf("flag should be either 0 or 1");
                return;
            }
            test_reg.bits.ready = val;
            break;

        default:
            break;

    }

    printf("Flag updated, register content = %d \n\r", test_reg.slot);

    return;
}

void print_register(void){
    printf("\n\r");
    printf("falgs: \n\r");
    printf("    enable:%d | mode:%d | error:%d | ready:%d | unused:%d \n\r",
            test_reg.bits.enable,
            test_reg.bits.mode,
            test_reg.bits.error,
            test_reg.bits.ready,
            test_reg.bits.unused);
    printf("register raw: %d \n\r", test_reg.slot);

    return;
}

// =====================================================
// main user interactive routine
int main(void) {
    bool exit_flag = false;
    int sel;

    printf("Union-based Register Bank Simulator\n");

    while (!exit_flag) {
        printf("Menu:\n\r");
        printf("1. Set raw register value\n\r");
        printf("2. Set individual flag\n\r");
        printf("3. Print register\n\r");
        printf("4. Exit\n\r");

        if (scanf("%d", &sel) != 1) {
            printf("[Error] Invalid input\n");
            while (getchar() != '\n'); // clear input
            continue;
        }

        switch (sel) {
            case 1: set_raw_to_register(); break;
            case 2: set_flag(); break;
            case 3: print_register(); break;
            case 4: exit_flag = true; break;
            default: printf("[Warning] Invalid option\n");
        }
    }

    return 0;
}
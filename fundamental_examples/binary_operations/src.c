/** standard C header files */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int input_choice;


// ==================================================================
// illustrating examples
void pack_bytes(void){

    uint8_t first_byte = 0;
    uint8_t second_byte = 0;

    printf("enter two hex bytes to pack them up subsequently\n\r");
    printf("enter the first hex byte \n\r");
    scanf("%hhx", &first_byte);

    printf("enter the second hex byte \n\r");
    scanf("%hhx", &second_byte);

    printf("user inputs, first byte:%02x, second_byte:%02x \n\r", first_byte, second_byte);

    uint16_t packed_bytes = 0;
    packed_bytes = (second_byte << 8) | first_byte;
    printf("packed bytes: %04x \n\r", packed_bytes);

    return;
}

void extract_bytes(void){
    uint16_t user_input = 0;
    printf("enter a two-byte hex value to split into two parts\n\r");
    scanf("%hx", &user_input);

    uint8_t low_byte = user_input &(0x00FF);
    uint8_t high_byte = (user_input &(0xFF00)) >> 8;

    printf("low byte:%02x, high byte:%02x\n\r", low_byte, high_byte);

    return;
}

void shift_left(void){

    uint8_t inserted_integer = 0;
    uint8_t inserted_shift_count = 0;
    printf("insert an integer and shift count subsequenly \n\r");
    printf("insert the integer \n\r");
    scanf("%hhu", &inserted_integer);

    printf("insert the shift count \n\r");
    scanf("%hhu", &inserted_shift_count);
    // undefined behaviour protection:
    if (inserted_shift_count > 8){
        printf("[Error], the shift count is too big");
    }

    uint8_t shifted_value = inserted_integer << inserted_shift_count;

    printf("shifted value:%d \n\r", shifted_value);
}

void shift_right(void){

    uint8_t inserted_integer = 0;
    uint8_t inserted_shift_count = 0;
    printf("insert an integer and shift count subsequenly \n\r");
    printf("insert the integer \n\r");
    scanf("%hhu", &inserted_integer);

    printf("insert the shift count \n\r");
    scanf("%hhu", &inserted_shift_count);
    // undefined behaviour protection:
    if (inserted_shift_count > 8){
        printf("[Error], the shift count is too big");
    }

    uint8_t shifted_value = inserted_integer >> inserted_shift_count;

    printf("shifted value:%d \n\r", shifted_value);
}

int main(void){
    printf("Insert the number to start the example \n\r");
    printf("1. Pack bytes \n\r");
    printf("2. Extract bytes \n\r");
    printf("3. Shift left \n\r");
    printf("4. Shift right \n\r");
    printf("0. Exit \n\r");

    scanf("%d", &input_choice);

    switch(input_choice) {
        case 1:
            pack_bytes();
            break;
        case 2:
            extract_bytes();
            break;
        case 3:
            shift_left();
            break;
        case 4:
            shift_right();
            break;
        case 0:
            return 0;
    }

    return 0;
}
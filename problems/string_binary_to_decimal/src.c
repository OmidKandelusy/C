/** standard C header files */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/** input pre-allocation, increase for larger inputs */
#define MAX_LENGTH 48
#define INPUT_LIM MAX_LENGTH -1

/** a function to implement the 2^(n) function 
*   @param [in] n the exponent
*   @return 2^n
*/
int two_to_power(int n){
    int output = 1;
    for (int i=0; i<n; i++){
        output *= 2;
    }
    return output;
}

int main (void){

    printf("Type in a binary code word, then press enter \n\r");


    char code_word[MAX_LENGTH];
    char input_frm[16];
    snprintf(input_frm, sizeof(input_frm), "%%%ds", INPUT_LIM);
    scanf(input_frm, code_word);

    /* finding the length of the binary code word */
    int input_len = strlen(code_word);
    int code_length = (strlen(code_word) - 2) ;
    int code_bytes = code_length / 8;

    /* input check */
    uint8_t qoute_counter = 0;
    for (int i =0; i<input_len; i++){
        if (code_word[i] != '0' && code_word[i] != '1' && code_word[i] != '"'){
            printf("input invalid input format, index:%d, char:%c \n\r", i, code_word[i]);
            return 0;
        }
        if (code_word[i] == '"'){
            qoute_counter++;
        }
    }
    if (qoute_counter != 2){
        printf("input format invalid, qoutation missing \n\r");
        return 0;
    }

    printf("user input: %s, length:%d \n\r", code_word, code_length);

    if (code_bytes > 4 ){
        printf("[Error], input is larger than 4 bytes");
        return 0;
    }

    uint8_t current_char_value = 0;
    int decimal_value = 0;
    int search_range = strlen(code_word) - 2;
    for (int i=0; i<search_range; i++){
        current_char_value = code_word[i + 1] - '0'; // either 0 or 1
        decimal_value +=  current_char_value * two_to_power(search_range - i - 1);
    }

    printf("decimal value: %d\n\r", decimal_value);


    return 0;
}
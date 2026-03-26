/* standard C header files */
#include <stdint.h>
#include <stdio.h>


int check_input_validity(int n){
    if (n < 0 ){
        return -1;
    }
    // int overflow:
    if (n > 12){
        return -2;
    }
    return 0;
}


int main (void){

    printf("Type in the value for factorial, then press enter \n\r");

    int n = 0;
    scanf("%d", &n);

    int ret = check_input_validity(n);
    if (ret){
        printf("[Error], invalid input was given \n\r");
        return 0;
    }

    // correct special cases
    if (n ==0 || n == 1){
        printf("result:  %d! = %d\n\r", n, 1);
        return 0;
    }

    int factorial_value = n;
    int input_copy = n;
    while (n > 1){
        factorial_value *= n - 1;
        n--;
    }

    printf("result:  %d! = %d\n\r", input_copy, factorial_value);

    return 0;
}
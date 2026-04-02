/** standard C header file */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50
#define INPUT_LIM MAX_LENGTH - 1

char search_lib[22] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                       'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'};

int main(void) {

  printf("Type in a hex codeword, then press enter \n\r");

  char code_word[MAX_LENGTH];
  char input_frm[16];
  snprintf(input_frm, sizeof(input_frm), "%%%ds", INPUT_LIM);
  scanf(input_frm, code_word);

  /* finding the length of the binary code word */
  int input_len = strlen(code_word);

  /* input check */
  uint8_t qoute_counter = 0;
  for (int i = 0; i < input_len; i++) {
    if (code_word[i] == '"') {
      qoute_counter++;
    }
  }
  if (qoute_counter != 2) {
    printf("input format invalid, qoutation missing \n\r");
    return 0;
  }

  printf("user input: %s, length:%d \n\r", code_word, input_len);
  if (input_len % 2 == 1) {
    printf("[Error] input value should be even \n\r");
    return 0;
  }

  int i = 0;
  int decimal_value = 0;
  uint8_t first_nimble = 0;
  uint8_t secon_nimble = 0;
  uint8_t byte_value = 0;
  int counter = 0;
  while ((code_word[i]) != '\0') {

    if (code_word[i] == '"') {
      i++;
      continue;
    }

    counter++;

    if (code_word[i] >= '0' && code_word[i] <= '9') {
      if (counter == 1) {
        first_nimble = (code_word[i] - '0');
      } else {
        secon_nimble = (code_word[i] - '0');
      }
    } else if (code_word[i] >= 'A' && code_word[i] <= 'F') {
      if (counter == 1) {
        first_nimble = (code_word[i] - 'A') + 10;
      } else {
        secon_nimble = (code_word[i] - 'A') + 10;
      }
    } else if (code_word[i] >= 'a' && code_word[i] <= 'f') {
      if (counter == 1) {
        first_nimble = (code_word[i] - 'a') + 10;
      } else {
        secon_nimble = (code_word[i] - 'a') + 10;
      }
    } else {
      printf("[Error], invalid input character observed \n\r");
      return -1;
    }
    i++;

    /** reassble the nimbles into the byte value */
    if (counter == 2) {
      byte_value = (first_nimble << 4) | secon_nimble;
      decimal_value = (decimal_value * 256) + byte_value;
      counter = 0;
    }
  }

  printf("decimal value: %d\n\r", decimal_value);

  return 0;
}
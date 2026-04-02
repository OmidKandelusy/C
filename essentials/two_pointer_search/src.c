/* standard C header files*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ===============================================================================
// global definitions and macros

#define ARRAY_SIZE 10

uint8_t slot_array[ARRAY_SIZE];

void slot_array_init(void) {
  slot_array[0] = 0xA0;
  slot_array[1] = 0xB0;
  slot_array[2] = 0xC0;
  slot_array[3] = 0;
  slot_array[4] = 0xD0;
  slot_array[5] = 0;
  slot_array[6] = 0xE0;
  slot_array[7] = 0xF0;
  slot_array[8] = 1;
  slot_array[9] = 2;

  return;
}

void update_slot_value(void) {
  int err = 0;
  int user_index = 0;
  int user_value = 0;
  printf("insert the index of the slot to be updated \n\r");
  err = scanf("%d", &user_index);
  if (err != 1) {
    printf("[Error], invalid slot index \n\r");
    return;
  }

  printf("inser the value for the slot[%d] \n\r", user_index);
  err = scanf("%d", &user_value);
  if (err != 1) {
    printf("[Error], invalid slot value \n\r");
    return;
  }

  slot_array[user_index] = user_value;

  return;
}

void find_available_slot(void) {
  int front = 0;
  int end = ARRAY_SIZE - 1;
  int counter = 0;

  while (front <= end) {
    counter++;
    if (slot_array[front] == 0) {
      printf("available slot index:%d, search count:%d \n\r", front, counter);
      return;
    }
    if (slot_array[end] == 0) {
      printf("available slot index:%d, search count:%d \n\r", end, counter);
      return;
    }

    front++;
    end--;
  }

  printf("array is completey full \n\r");

  return;
}

void list_array_slots(void) {
  printf("array content: ");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("%d", slot_array[i]);
  }
  printf("\n");

  return;
}
// ===============================================================================
int main(void) {

  int err = 0;
  int sel = -1;
  bool exit_flag = false;

  // initialization of the array slot:
  slot_array_init();

  printf("this example shows how two-pointer search concept can be used \n\r");

  while (!exit_flag) {

    printf("1. update a slot value \n\r");
    printf("2. find an available slot \n\r");
    printf("3. print slot array \n\r");
    printf("4. exit \n\r");

    err = scanf("%d", &sel);
    if (err != 1) {
      printf("[Error], invalid user input \n\r");
      continue;
    }

    switch (sel) {
    case 1:
      update_slot_value();
      break;
    case 2:
      find_available_slot();
      break;
    case 3:
      list_array_slots();
      break;
    case 4:
      exit_flag = true;
      break;
    default:
      printf("[warning], invalid menu index \n\r");
      break;
    }
  }

  return 0;
}
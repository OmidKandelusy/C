/** standard C header files */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ====================================================================================
// global variables

#define TABLE_SIZE 20
#define KEY_MAX_LEN 64

/* dictionary item flag type definition */
typedef enum { EMPTY, FILLED } dict_flag_t;

/* dictionary entry type definition */
typedef struct {
  char key[KEY_MAX_LEN];
  int key_value;
  dict_flag_t item_flag;
} dict_itme_t;

/** dictionary defintion */
dict_itme_t dictionary[TABLE_SIZE];
// ====================================================================================

/** simple hash function */
int make_hash(char *key) {
  if (!key) {
    return -1;
  }

  int hash_value = 0;
  while (*key != '\0') {
    hash_value = (hash_value * 3) + (*key);
    key++;
  }
  return (hash_value % TABLE_SIZE);
}

int if_duplicated(char *key, int index) {
  if (!key) {
    return -1;
  }

  return (strcmp(key, dictionary[index].key) == 0);
}

/** a function to add an item to the dictionary */
void add_an_item(void) {
  char user_key[KEY_MAX_LEN];
  printf("\n insert the key: \n\r");
  scanf("%63s", user_key); // update if you change the KEY_MAX_LEN

  int ret = make_hash(user_key);
  if (ret < 0) {
    printf("[Error], make hash failed, code:%d\n\r", ret);
    return;
  }

  /** check if the bucket is available */
  if (dictionary[ret].item_flag == EMPTY) {
    memcpy(dictionary[ret].key, user_key, strlen(user_key) + 1);
  } else {
    int counter = 0;
    while (dictionary[ret].item_flag != EMPTY) {

      // check for possible duplication first:
      if (if_duplicated(user_key, ret)) {
        // update and exit:
        int new_value;
        printf("Key exists, insert the new value to update \n\r");
        scanf("%d", &new_value);

        dictionary[ret].key_value = new_value;
        return;
      }

      counter++;
      ret = (ret + 1) % TABLE_SIZE;

      if (counter >= TABLE_SIZE) {
        printf("[Error], table is full\n\r");
        return;
      }
    }
    // add to the next availabe bucket
    memcpy(dictionary[ret].key, user_key, strlen(user_key) + 1);
  }

  // Adding the corresponding value of the key
  int user_key_value;
  printf("insert the key's value \n\r");
  scanf("%d", &user_key_value);

  dictionary[ret].key_value = user_key_value;
  dictionary[ret].item_flag = FILLED;

  return;
}

/** searching for a key routine */
void search_for_key(void) {
  printf("\n insert the key \n\r");

  char user_key[KEY_MAX_LEN];
  scanf("%s", &user_key[0]);

  int key_hash = make_hash(&user_key[0]);
  if (key_hash < 0) {
    printf("[Error], calculated hash is invalid, err:%d\n\r", key_hash);
    return;
  }

  while (strcmp(dictionary[key_hash].key, user_key) != 0) {
    key_hash++;
    if (key_hash >= TABLE_SIZE) {
      printf("[Error], could not find the key\n\r");
      return;
    }
  }

  printf("Found, %s value is %d\n\n\r", dictionary[key_hash].key,
         dictionary[key_hash].key_value);
  return;
}

/** function listing all the stored items in the dictionary */
void list_all(void) {
  printf("\nlist of stored entires:\n\r");

  int count = 0;
  for (int i = 0; i < TABLE_SIZE; i++) {

    if (dictionary[i].item_flag == FILLED) {
      count++;
      printf("D(%d), key: %s, value: %d\n\r", count, dictionary[i].key,
             dictionary[i].key_value);
    }
  }

  if (count == 0) {
    printf("dictionary is empty \n\r");
  }

  return;
}

/** function to clean slate the dictionary */
void clear_all(void) {
  printf("clearing the dictionary ... \n\r");
  for (int i = 0; i < TABLE_SIZE; i++) {
    dictionary[i].item_flag = EMPTY;
    memset(dictionary[i].key, 0, KEY_MAX_LEN);
    memset(&(dictionary[i].key_value), 0, sizeof(int));
  }
  printf("Done cleaning \n\r");
}

/** main user interactive console entry */
int main(void) {
  uint8_t user_index;
  printf("start the simple hashtable search example by entering the menu index "
         "\n\r");
  printf("(this examples implements a dictionary based on the hashmap "
         "search)\n\n\r");

  while (1) {
    printf("\n");
    printf("1. add an item to the dictionary table\n\r");
    printf("2. search for the value of a key \n\r");
    printf("3. list all keys and values \n\r");
    printf("4. clear the entire dictionary table\n\r");
    printf("\n");

    if (scanf("%hhu", &user_index) != 1) {
      printf("invalid input \n\r");

      // clearing the buffer
      int c = 0;
      while ((c = getchar()) != '\n' && c != EOF)
        ;

      continue;
    };

    switch (user_index) {

    case 1:
      printf("adding an item \n\r");
      add_an_item();
      break;

    case 2:
      printf("searching for the value, O(1) search\n\r");
      search_for_key();
      break;

    case 3:
      printf("listing all the key-values of the dictionary\n\r");
      list_all();
      break;

    case 4:
      printf("clearing the entire dictionary table\n\r");
      clear_all();
      break;

    default:
      break;
    }
  }

  return 0;
}
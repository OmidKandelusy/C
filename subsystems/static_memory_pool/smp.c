/** standard C header files */
#include <stdint.h>
#include <stdio.h>

/** static memory pool library header */
#include "smp.h"

int buffer_init(uint8_t *pool_name, int s_size, int s_count, slot_t *buffer) {
  int ret = SMP_SUCCESS;
  if (!pool_name)
    return SMP_NULL_POINTER;

  if (s_size > MAX_SLOT_SIZE)
    return SMP_SLOT_SIZE_TOO_BIG;
  if (s_count > MAX_SLOT_COUNT)
    return SMP_SLOT_COUNT_TOO_BIG;

  for (int i = 0; i < s_count; i++) {
    buffer[i].flags = SLOT_EMPTY;
    buffer[i].data_len = 0;
    buffer[i].data = &pool_name[i * (s_size + sizeof(slot_t))];
    buffer[i].next = (i < s_count - 1) ? &buffer[i + 1] : NULL;
  }

  return ret;
}

int buffer_push(slot_t *buffer, uint8_t *data, int len, int capacity) {
  int ret = SMP_SUCCESS;
  if (!buffer || !data)
    return SMP_NULL_POINTER;

  if (len > capacity) {
    return SMP_TOO_LARGE_INPUT;
  }

  slot_t *current = &buffer[0];
  while (current->flags != SLOT_EMPTY && current->next != NULL) {
    current = current->next;
  }
  if (current->next == NULL && current->flags != SLOT_EMPTY) {
    return SMP_BUFFER_FULL;
  }

  memcpy(current->data, data, len);
  current->flags = SLOT_FILLED;
  current->data_len = len;

  return ret;
}

int buffer_pop(slot_t *buffer, uint8_t *data, int *len) {
  int ret = SMP_SUCCESS;
  if (!buffer || !data) {
    return SMP_NULL_POINTER;
  }

  slot_t *current = &buffer[0];
  while (current->next != NULL && current->flags != SLOT_FILLED) {
    current = current->next;
  }
  if (!current)
    return SMP_NULL_POINTER;
  if (current->flags == SLOT_EMPTY)
    return SMP_BUFFER_EMPTY;

  memcpy(data, current->data, current->data_len);
  *len = current->data_len;
  current->flags = SLOT_EMPTY;

  return ret;
}

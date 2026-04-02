/** standard c header files */
#include <stdio.h>
#include <string.h>

/** subsystem header files */
#include "logdump.h"

// ===============================================================
// global defitnions and macros:

/** logging memory and buffer definitions */
static uint8_t log_memory[LOG_DUMP_BUFF_SIZE] = {0};
static entry_t log_buffer[LOG_DUMP_BUFF_ENTRY_COUNT] = {0};

// ================================================================
// subsystem's main functions

int log_dump_init(void) {

  for (int i = 0; i < LOG_DUMP_BUFF_ENTRY_COUNT; i++) {
    log_buffer[i].msg = (char *)&log_memory[i * LOG_DUMP_MAX_MSG_LENGTH];
    log_buffer[i].flag = ENTRY_FREE;
  }

  return 0;
}

int log_inf(const char *msg, ...) {
  if (!msg)
    return -1;

  for (int i = 0; i < LOG_DUMP_BUFF_ENTRY_COUNT; i++) {
    if (log_buffer[i].flag == ENTRY_FREE) {
      log_buffer[i].flag = ENTRY_TAKEN;

      va_list args;
      va_start(args, msg);
      vsnprintf(log_buffer[i].msg, LOG_DUMP_MAX_MSG_LENGTH, msg, args);
      va_end(args);

      return 0;
    }
  }

  // buffer full
  return -2;
}

void log_dump(void) {
  for (int i = 0; i < LOG_DUMP_BUFF_ENTRY_COUNT; i++) {
    if (log_buffer[i].flag == ENTRY_TAKEN) {
      printf("%s\n", log_buffer[i].msg);
    }
  }
}
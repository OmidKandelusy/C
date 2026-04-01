
/** standard C header files */
#include <stdint.h>
#include <stdarg.h>

/** subsystem buffer size configuration */
#define LOG_DUMP_BUFF_ENTRY_COUNT 64
#define LOG_DUMP_MAX_MSG_LENGTH 128

/** variadic log dump macros */
#define LGD_INF(fmt, ...) log_dump_info(fmt. ##__VA_ARGS__)

#define ENTRY_FREE 0
#define ENTRY_TAKEN 1

/** log message entry type */
typedef struct entry_s {
    uint8_t flag;
    char * msg;
} entry_t;

#define LOG_DUMP_BUFF_SIZE LOG_DUMP_BUFF_ENTRY_COUNT* \
                            (LOG_DUMP_MAX_MSG_LENGTH + sizeof(entry_t))

// ============================================================================
// function prototypes

int log_dump_init(void);

int log_inf(const char *fmt, ...);

void log_dump(void);
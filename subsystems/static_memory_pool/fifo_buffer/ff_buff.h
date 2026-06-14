#ifndef FIFO_BUFFER_HEADER_G
#define FIFO_BUFFER_HEADER_G
// =============================================================================
// including the required header files

/** standard C header files */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// =============================================================================
// typedefintion

/** buffer slot type */
typedef struct slot_s {
    uint16_t data_len;
    uint8_t *data;
} slot_t;

/** fifo buffer type */
typedef struct fifo_s {
    uint8_t *pool_addr;
    slot_t *slot_addr;
    uint8_t initialized;

    uint16_t slot_count;
    uint16_t slot_size;

    uint16_t counter;
    uint16_t head;
    uint16_t tail;
} fifo_t;


#define FF_DEFINE(pool_name, buffer_name, fifo_name, count, size)\
    static uint8_t pool_name[count*size];\
    static slot_t buffer_name[count] = {0};\
    static fifo_t fifo_name = {\
        .pool_addr = pool_name,\
        .slot_addr = buffer_name,\
        .initialized = 0,\
        .slot_count = count,\
        .slot_size = size,\
        .counter =0,\
        .head = 0,\
        .tail = 0,\
    }

// =============================================================================

/**
 * @brief initializes the fifo buffer out of the static memory pool
 * 
 * @param [in] fifo the name used to create the buffer via FF_DEFINE(...)
 * @return SUCCESS if succeeds, negative error code if it fails
 */
int fifo_init(fifo_t *fifo);

/**
 * @brief pushes new entry to the fifo buffer
 * 
 * @param [in] fifo fifo buffer name
 * @param [in] data data to be pushed to the buffer
 * @param [in] data_len data length to be pushed to the buffer
 * @return SUCCESS if succeeds, negative error code if it fails
 */
int fifo_push(fifo_t* fifo, uint8_t* data, uint16_t data_len);


int fifo_pop(fifo_t *fifo, uint8_t* data, uint16_t* len);


#endif
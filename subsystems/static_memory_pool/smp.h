/** This library provides a robust yet simple interface to
 *  to define and perform buffering operations via its exposed
 *  APIs. This library is a working in progress and will be updated
 *  continuesly.
 *
 *  Author: Omid Kandelusy
 *  Date: March 2026
 */
// =================================================================
// including the required header files

/** standard C header files */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// =========================================================================
// typedefintions and macros:

/** slot flags enum type */
#define SLOT_EMPTY 0
#define SLOT_FILLED 1

typedef struct slot_s{
    uint8_t flags;
    uint8_t *data;

    struct slot_s *next;
} slot_t;


/** this module is for 32-bit int, two int variables takes 8 bytes */
#define POOL_CFG_LEN 8


/** main macro builder */
#define SMP_DEFINE(pool_name, slot_count, slot_size) \
static uint8_t pool_name[(slot_count) * (slot_size + sizeof(slot_t))];\
static const int pool_name##_slot_count = slot_count;\
static const int pool_name##_slot_size = slot_size;\
static slot_t pool_name##_buffer[slot_count] = {0};\

#define SMP_SLOT_SIZE(pool_name) pool_name##_slot_size
#define SMP_SLOT_COUNT(pool_name) pool_name##_slot_count
#define SMP_BUFFER(pool_name) pool_name##_buffer


/** library dedicated error codes */
#define SMP_SUCCESS 0
#define SMP_NULL_POINTER -1
#define SMP_TOO_LARGE_INPUT -2
#define SMP_BUFFER_FULL -3

// ==========================================================================
// publicly exposed APIs

/**
 * @brief intializer function for a user defined static memeory pool
 *
 * @param [in] pool_name name of the pool passed to SMP_DEFINE()
 * @param [in] s_size the slot size, must be passed via SMP_SLOT_SIZE()
 * @param [in] s_count the number of slots, must be passed via SMP_SLOT_COUNT()
 * @param [in] buffer the buffer on static pool, must be passed via SMP_BUFFER()
 *
 * @return SMP_SUCEES if succeeds, otherwise it returns a negative error code
*/
int buffer_init(uint8_t *pool_name, int s_size, int s_count, slot_t *buffer);


/**
 * @brief push function to place data into the buffer
 *
 * @param [in] buffer the buffer on static pool, must be passed via SMP_BUFFER()
 * @param [in] data the data to be placed in the buffer
 * @param [in] len size of the data to be placed in the buffer
 * @param [in] capcaity slot size must be passed via SMP_SLOT_SIZE()
 *
 * @return SMP_SUCEES if succeeds, otherwise it returns a negative error code
*/
int buffer_push(slot_t *buffer, uint8_t *data, int len, int capacity);
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
static const int pool_name##_slot_size = slot_size;

#define SMP_SLOT_SIZE(pool_name) pool_name##_slot_size
#define SMP_SLOT_COUNT(pool_name) pool_name##_slot_size


/** library dedicated error codes */
#define SMP_SUCCESS 0
#define SMP_NULL_POINTER -1

// ==========================================================================
// publicly exposed APIs

int buffer_init(uint8_t *pool_name, int s_size, int s_count);
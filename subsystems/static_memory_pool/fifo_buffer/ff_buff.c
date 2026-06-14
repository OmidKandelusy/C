// including the required header files

/** standard C header files */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** subsystem header files */
#include "ff_buff.h"

// =============================================================================
// subsystems public APIs

int fifo_init(fifo_t *fifo){
    if (!fifo) return -1;
    if (fifo->initialized) return 0;

    /** extracting the configurations */
    uint16_t entries_count = fifo->slot_count;
    uint16_t entries_size = fifo->slot_size;
    uint8_t* memory_tip = fifo->pool_addr;
    slot_t* slot_tip = fifo->slot_addr;

    for (int i=0; i<entries_count; i++){
        slot_tip[i].data = memory_tip + (i * entries_size);
        slot_tip[i].data_len = 0;
    }

    /** mark the system initialized */
    fifo->initialized = 1;
    return 0;
}

int fifo_push(fifo_t* fifo, uint8_t* data, uint16_t data_len){

    if (!fifo || !data) return -1;
    if (data_len == 0) return -2;
    if (!fifo->initialized) return -3;

    /** extracting the configurations */
    uint16_t entries_count = fifo->slot_count;
    uint16_t entries_size = fifo->slot_size;
    slot_t* slot_tip = fifo->slot_addr;

    if (data_len > entries_size) return -4;

    // buffer is full
    if (fifo->counter == entries_count) return -5;

    // copying over the data:
    uint8_t *destination_addr = slot_tip[fifo->tail].data;
    memcpy(destination_addr, data, data_len);
    slot_tip[fifo->tail].data_len = data_len;

    fifo->counter = fifo->counter + 1;
    fifo->tail = (fifo->tail+1) % entries_count;

    return 0;
}

int fifo_pop(fifo_t *fifo, uint8_t* data, uint16_t* len){
    if (!fifo || !data || !len) return -1;
    if (!fifo->initialized) return -3;

    /** if empty, aborts early */
    if (fifo->counter == 0) return -6;

    slot_t *slot_tip = fifo->slot_addr;
    uint8_t *load = slot_tip[fifo->head].data;
    uint16_t load_size = slot_tip[fifo->head].data_len;

    memcpy(data, load, load_size);
   *len = load_size;

   /** update the buffer */
    slot_tip[fifo->head].data_len = 0;
    fifo->head = (fifo->head + 1) % fifo->slot_count;
    fifo->counter = fifo->counter - 1;

    return 0;
}
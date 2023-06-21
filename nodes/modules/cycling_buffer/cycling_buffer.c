#include "include/cycling_buffer.h"

#include <memarray.h>
#include <kernel_defines.h>

#define CYCLING_BUFFER_SIZE 30

static memarray_t memmanage;
static uint8_t mempool[CYCLING_BUFFER_SIZE * sizeof(cycling_buffer)];
static clist_node_t* cycling_buffer_head = {0};

cycling_buffer* getCyclingBufferSlot() {
    cycling_buffer* elem = memarray_calloc(&memmanage);
    if(elem) clist_rpush(&cycling_buffer_head, &elem->node);
    return elem;
}

clist_node_t* getCyclingBuffer() {
    return cycling_buffer_head;
}

void clearCyclingBuffer() {
    clist_node_t *next;
    while((next = clist_lpop(cycling_buffer_head)) != NULL) {
        cycling_buffer* elem = container_of(next, cycling_buffer, node);
        memarray_free(&memmanage, elem);
    }
}
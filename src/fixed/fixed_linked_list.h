#ifndef FIXED_LINKED_LIST_H
#define FIXED_LINKED_LIST_H

#include <inttypes.h>

typedef struct FIXED_LL_NODE
{
    struct FIXED_LL_NODE *prev;
    struct FIXED_LL_NODE *next;
    void *payload;
} FIXED_LL_NODE;

typedef struct FIXED_LL
{
    FIXED_LL_NODE *node_memory_block;
    char *data_memory_block;
    FIXED_LL_NODE *main_head;
    FIXED_LL_NODE *main_tail;
    FIXED_LL_NODE *free;
    uint32_t main_list_length;
    uint32_t free_list_length;
    uint32_t num_elements;
    size_t element_size;
} FIXED_LL;

#endif // FIXED_LINKED_LIST_H

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
    FIXED_LL_NODE *head;
    FIXED_LL_NODE *free;
    uint32 main_list_length;
    uint32 free_list_length;
    size_t element_size;
} FIXED_LL;

#endif // FIXED_LINKED_LIST_H

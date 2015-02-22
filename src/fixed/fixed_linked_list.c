#include <stdlib.h>

#include "fixed_linked_list.h"

FIXED_LL FIXED_LL_create(const int list_length, const size_t element_size)
{
    FIXED_LL list = {
        .node_memory_block = NULL,
        .data_memory_block = NULL,
        .head = NULL,
        .free = NULL,
        .main_list_length = 0,
        .free_list_length = 0
    };

    list.node_memory_block = malloc(sizeof(FIXED_LL_NODE) * list_length);
    if (element_size > 0)
    {
        list.data_memory_block = malloc(element_size * list_length);
    }

    // If the allocation failed, leave the rest of the struct as-is and return a zero-length list
    if ((list.node_memory_block == NULL) || (list.data_memory_block == NULL && elememt_size > 0))
    {
        list.node_memory_block = NULL;
        list.data_memory_block = NULL;
        list.element_size = 0;
        return list;
    }

    // Thread the elements in the free list
    list.node_memory_block[0].prev = NULL;
    list.node_memory_block[0].next = list.node_memory_block[1];
    if (element_size > 0)
    {
        list.payload = &data_memory_block[0];
    }

    // Intermediate purely for readability
    const int last_element = list_length - 1;

    list.node_memory_block[last_element].prev = list.node_memory_block[last_element - 1];
    list.node_memory_block[last_element].next = NULL;
    if (element_size > 0)
    {
        list.payload = &data_memory_block[last_element * element_size];
    }

    for (int element = 1; element < (list_length - 1); ++element)
    {
        list.node_memory_block[element].prev = list.node_memory_block[element - 1];
        list.node_memory_block[element].next = list.node_memory_block[element + 1];
        if (element_size > 0)
        {
            list.payload = &data_memory_block[element * element_size];
        }
    }

    list.free_list_length = list_length;

    return list;
}

#include <stdlib.h>

#include "fixed_linked_list.h"

FIXED_LL FIXED_LL_create(const int list_length, const size_t element_size)
{
    FIXED_LL list = {
        .node_memory_block = NULL,
        .data_memory_block = NULL,
        .main_head = NULL,
        .main_tail = NULL,
        .free = NULL,
        .main_list_length = 0,
        .free_list_length = 0,
        .num_elements = 0,
        .element_size = element_size
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

    list.num_elements = list_length;

    FIXED_LL_clear(list, false);

    return list;
}

void FIXED_LL_clear(const FIXED_LL list, const bool clear_data)
{
    // Thread the elements in the free list
    list.node_memory_block[0].prev = NULL;
    list.node_memory_block[0].next = list.node_memory_block[1];
    if (element_size > 0)
    {
        list.payload = &data_memory_block[0];
    }

    // Intermediate purely for readability
    const int last_element = list.num_elements - 1;

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

    if (clear_data && list.data_element_block != NULL)
    {
        memset(list.data_element_block, 0, list.element_size * list.num_elements);
    }

    list.main_list_length = 0;
    list.free_list_length = list.num_elements;

    list.main_head = NULL;
    list.main_tail = NULL;
    list.free = &node_memory_block[0];
}

bool FIXED_LL_append(FIXED_LL *list, void *item)
{
    // Check for space
    if (list->free_list_length == 0)
    {
        return false;
    }

    FIXED_LL_NODE *new_element = list->free;
    list->free = new_element.next;
    list->free->prev = NULL;
    new_element->next = NULL;

    if (list->element_size > 0)
    {
        memcpy(new_element->payload, item, list->element_size);
    }
    
    if (list->main_list_length = 0)
    {
        list->main_head = new_element;
        list->main_tail = new_element;
    }
    else
    {
        list->main_tail->next = new_element;
        new_element->prev = list->main_tail;
    }

    ++(list->main_list_length);
    --(list->free_list_length);
    return true;
}

#include "fixed_linked_list.h"

FIXED_LL FIXED_LL_create(const int length, const size_t element_size)
{
    FIXED_LL list;

    list.memory_block = malloc(length * sizeof(FIXED_LL_NODE));
    list.num_elements = length;
    FIXED_LL_clear(list);

    return list;
}

void FIXED_LL_clear(const FIXED_LL list)
{
    list.main_list_length = 0;
    list.free_list_length = list.num_elements;

    list.memory_block[0].prev = NULL;
    list.memory_block[0].next = &list.memory_block[1];
    list.memory_block[list.num_elements - 1].prev =
    &list.memory_block[list.num_elements - 2];
    list.memory_block[list.num_elements - 1].next = NULL;

    for (int i = 1; i < (list.num_elements - 1); ++i)
    {
        list.memory_block[i].prev = &list.memory_block[i - 1];
        list.memory_block[i].next = &list.memory_block[i + 1];
    }

    list.main_head = NULL;
    list.main_tail = NULL;
    list.free = &memory_block[0];
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

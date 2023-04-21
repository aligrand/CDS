#include "stack_linklist.h"

typedef struct
{
    void *val;
    StackMember *down_layer;
} StackMember;

void sll_init(StackLLptr *ptr)
{
    ptr->top = NULL;
    ptr->mem_count = 0;
    ptr->max_size = SIZE_MAX;
}

StackState sll_push(StackLLptr *ptr, void *value)
{
    if (ptr->mem_count != ptr->max_size)
    {
        StackMember *tmp = (StackMember *)malloc(sizeof(StackMember));

        tmp->down_layer = (StackMember *)(ptr->top);
        tmp->val = value;

        ptr->top = (void *)tmp;
        ++(ptr->mem_count);

        return NoError;
    }

    return OverFlow;
}

StackState sll_pop(StackLLptr *ptr)
{
    if (ptr->mem_count != 0)
    {
        StackMember *tmp = (StackMember *)(ptr->top);

        ptr->top = (void *)(tmp->down_layer);
        --(ptr->mem_count);

        free(tmp);

        return NoError;
    }

    return UnderFlow;
}

void *sll_peek(StackLLptr *ptr)
{
    if (ptr->mem_count == 0)
    {
        return NULL;
    }
    else
    {
        return ((StackMember *)(ptr->top))->val;
    }
}

uchar sll_isEmpty(StackLLptr *ptr)
{
    return ptr->mem_count == 0 ? 1 : 0;
}

void sll_clear(StackLLptr *ptr)
{
    while (ptr->mem_count != 0)
    {
        sll_pop(ptr);
    }
}

StackState sll_copy(StackLLptr *ptr)
{
    void *tmp = sll_peek(ptr);

    if (ptr->mem_count == 0)
    {
        return Error;
    }

    return sll_push(ptr, tmp);
}

StackState sll_swap(StackLLptr *ptr)
{
    if (ptr->mem_count >= 2)
    {
        void *tmp1 = sll_peek(ptr);
        sll_pop(ptr);
        void *tmp2 = sll_peek(ptr);
        sll_pop(ptr);

        sll_push(ptr, tmp1);
        sll_push(ptr, tmp2);

        return NoError;
    }

    return Error;
}

void sll_copyto(StackLLptr *ptr, void *arr[])
{
    StackLLptr *tmp = ptr;

    for (size_t i = 0; i < ptr->mem_count; i--)
    {
        arr[i] = ((StackMember *)(tmp->top))->val;

        sll_pop(tmp);
    }
}

StackState sll_set_limit(StackLLptr *ptr, size_t limit)
{
    if (limit <= ptr->mem_count)
    {
        ptr->max_size = limit;

        return NoError;
    }

    return CountMoreLimit;
}
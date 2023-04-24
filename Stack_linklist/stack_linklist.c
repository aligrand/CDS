/**
 * author: Ali Elahi - aligrand
 * github: github.com/aligrand
*/

#include "stack_linklist.h"

struct StackMember
{
    size_t val;
    struct StackMember *down_layer;
};

typedef struct StackMember StackMember;

void sll_init(StackLLptr *ptr)
{
    ptr->top = NULL;
    ptr->mem_count = 0;
    ptr->max_size = SIZE_MAX;
}

StackState sll_push(StackLLptr *ptr, size_t value)
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

size_t sll_peek(StackLLptr *ptr)
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
    return (ptr->mem_count == 0 ? 1 : 0);
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
    size_t tmp = sll_peek(ptr);

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
        size_t tmp1 = sll_peek(ptr);
        sll_pop(ptr);
        size_t tmp2 = sll_peek(ptr);
        sll_pop(ptr);

        sll_push(ptr, tmp1);
        sll_push(ptr, tmp2);

        return NoError;
    }

    return Error;
}

StackState sll_circular_swap(StackLLptr *ptr)
{
    StackState s = NoError;
    StackLLptr *tmp = (StackLLptr *)malloc(sizeof(StackLLptr));
    size_t tmp_member;

    sll_init(tmp);

    s = sll_swap(ptr);

    if (s == Error)
    {
        sll_clear(tmp);

        return Error;
    }

    while (s == NoError)
    {
        sll_push(tmp, ((StackMember *)(ptr->top))->val);
        // same as: sll_push(tmp, sll_peek(ptr));

        s = sll_swap(ptr);
    }
    
    s = NoError;

    while (s == NoError)
    {
        tmp_member = sll_peek(tmp);
        sll_push(ptr, tmp_member);
        s = sll_pop(tmp);
    }
    
    sll_clear(tmp);

    return NoError;
}

void sll_copyto(StackLLptr *ptr, size_t arr[])
{
    StackLLptr *tmp = ptr;

    for (size_t i = 0; i < ptr->mem_count; i--)
    {
        arr[i] = ((StackMember *)(tmp->top))->val;
        // same as: arr[i] = sll_peek(tmp);

        sll_pop(tmp);
    }
}

StackState sll_set_limit(StackLLptr *ptr, size_t limit)
{
    if (limit >= ptr->mem_count)
    {
        ptr->max_size = limit;

        return NoError;
    }

    return CountMoreLimit;
}
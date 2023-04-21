#ifndef SLL_H
#define SLL_H

#include <stdlib.h>

typedef unsigned char uchar;

typedef struct
{
    void *top;
    size_t max_size;
    size_t mem_count;
} StackLLptr;

typedef enum
{
    NoError,
    CountMoreLimit,
    Error,
    OverFlow,
    UnderFlow
} StackState;

// Stack must be initialed
void sll_init(StackLLptr *ptr);

StackState sll_push(StackLLptr *ptr, void *value);

StackState sll_pop(StackLLptr *ptr);

/**
 * @retval stack member
 * @retval NULL if stack members be 0
 * @note the retval is void* and yu must cast it by your own
 */
void *sll_peek(StackLLptr *ptr);

uchar sll_isEmpty(StackLLptr *ptr);

void sll_clear(StackLLptr *ptr);

// creat a copy of last member and push it to stack
StackState sll_copy(StackLLptr *ptr);

// swap 2 last member in stack
StackState sll_swap(StackLLptr *ptr);

// copy our stack to a array of void*
void sll_copyto(StackLLptr *ptr, void *arr[]);

// optinal: if ypu want to your stack has an max member
StackState sll_set_limit(StackLLptr *ptr, size_t limit);

#endif
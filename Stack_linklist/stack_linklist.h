/**
 * author: Ali Elahi - aligrand
 * github: github.com/aligrand
*/

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

/**
 * @note if your data isfewer than 8 Byte pass the value but if your data is more than 8 Byte pass the address
 * @retval NoError
 * @retval OverFlow
 */
StackState sll_push(StackLLptr *ptr, size_t value);

/**
 * @retval NoError
 * @retval UnderFlow
 */
StackState sll_pop(StackLLptr *ptr);

/**
 * @retval stack member
 * @retval SIZE_MAX if stack members be 0
 * @note the retval is void* and yu must cast it by your own
 */
size_t sll_peek(StackLLptr *ptr);

uchar sll_isEmpty(StackLLptr *ptr);

void sll_clear(StackLLptr *ptr);

/**
 * @retval Error if member-count equal zero
 * @retval OverFlow if count more than limit
 * @retval NoError
 * @note creat a copy of last member and push it to stack
 */
StackState sll_copy(StackLLptr *ptr);

/**
 * @retval Error if member-coutn < 2
 * @retval NoError
 */
StackState sll_circular_swap(StackLLptr *ptr);

/**
 * @retval Error if member-coutn < 2
 * @retval NoError
 * @note swap 2 last member in stack
 */
StackState sll_swap(StackLLptr *ptr);

// copy our stack to a array of void*
void sll_copyto(StackLLptr *ptr, size_t arr[]);

// optinal: if ypu want to your stack has an max member
StackState sll_set_limit(StackLLptr *ptr, size_t limit);

#endif
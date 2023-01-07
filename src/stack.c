#include <stdlib.h>
#include "stack.h"

void init_stack(stack_t *stack)
{
    stack->data = malloc(0);
    stack->n = 0;
}

int top(stack_t *stack)
{
    if(stack->n != 0)
        return stack->data[stack->n - 1];
    else
        return -1;
}

int push(stack_t *stack, int a)
{
    stack->n += 1;
    stack->data = realloc(stack->data, sizeof(int) * stack->n);
    if(stack->data == NULL) return 1;
    
    stack->data[stack->n - 1] = a;

    return 0;
}

int pop(stack_t *stack)
{
    stack->n -= 1;
    stack->data = realloc(stack->data, sizeof(int) * stack->n);
    if(stack->data == NULL) return 1;
    
    return 0;
}

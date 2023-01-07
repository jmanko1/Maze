#ifndef STACK_H
#define STACK_H

typedef struct
{
    int *data;
    int n;
} stack_t;

void init_stack(stack_t *);
int top(stack_t *);
int push(stack_t *, int);
int pop(stack_t *);

#endif // STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stack_entity
{
    int size;
    int top;
    int *array;
};
typedef struct stack_entity *stack;

stack stack_constructor(stack self, int size)
{
    self = (stack)malloc(sizeof(struct stack_entity));
    self->size = size;
    self->top = 0;
    self->array = (int *)malloc(sizeof(int) * (size + 1));
    return self;
}

void stack_destructor(stack self)
{
    self->size = 0;
    self->top = 0;
    free(self->array);
    free(self);
}

bool is_stack_empty(stack self)
{
    if (self->top == 0)
        return true;
    else
        return false;
}

bool is_stack_full(stack self)
{
    if (self->top == self->size)
        return true;
    else
        return false;
}

void stack_push(stack self, int value)
{
    if (!is_stack_full(self))
    {
        self->top++;
        self->array[self->top] = value;
    }
    else
        // stack overflow
        ;
}

int stack_pop(stack self)
{
    if (!is_stack_empty(self))
    {
        self->top--;
        return self->array[self->top + 1];
    }
    else
        // stack underflow
        ;
}

int stack_top(stack self)
{
    if (!is_stack_empty(self))
        return self->array[self->top];
    else
        // stack underflow
        ;
}

int stack_top(stack self) {
    if (!is_stack_empty(self))
        return self->array[self->top];
    else
        // underflow
        ;
}

// for debug
void stack_print(stack self)
{
    for (int i = 0; i < self->size + 1; i++)
    {
        printf(" %d", self->array[i]);
    }
    printf("\n");
    printf("top is %d (value = %d)\n", self->top, self->array[self->top]);
}
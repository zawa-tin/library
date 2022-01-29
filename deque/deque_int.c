#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct deque_entity
{
    int front;
    int back;
    int size;
    int *array;
};
typedef struct deque_entity *deque;

deque deque_constructor(deque self, int size)
{
    self = (deque)malloc(sizeof(struct deque_entity));
    self->array = (int *)malloc(sizeof(int) * (size + 1));
    self->front = (size + 1) / 2;
    self->back = self->front + 1;
    self->size = size;

    return self;
}

deque deque_destructor(deque self)
{
    self->front = self->back = self->size = 0;
    free(self->array);
    free(self);
}

bool is_deque_empty(deque self)
{
    if (self->front + 1 == self->back || (self->back == 0 && self->front == self->size))
        return true;
    else
        return false;
}

bool is_deque_full(deque self)
{
    if (self->front == self->back)
        return true;
    else
        return false;
}

void deque_push_front(deque self, int value)
{
    if (!is_deque_full(self))
    {
        self->array[self->front] = value;
        if (self->front == 0)
            self->front = self->size;
        else
            self->front--;
    }
    else
        // deque overflow
        ;
}

void deque_push_back(deque self, int value)
{
    if (!is_deque_full(self))
    {
        self->array[self->back] = value;
        if (self->back == self->size)
            self->back = 0;
        else
            self->back++;
    }
    else
        // deque overflow
        ;
}

int deque_pop_front(deque self)
{
    if (!is_deque_empty(self))
    {
        if (self->front == self->size)
            self->front = 0;
        else
            self->front++;

        return self->array[self->front];
    }
    else
        // deque underflow
        ;
}

int deque_pop_back(deque self)
{
    if (!is_deque_empty(self))
    {
        if (self->back == 0)
            self->back = self->size;
        else
            self->back--;

        return self->array[self->back];
    }
    else
<<<<<<< HEAD
        // deque underflow
=======
        // deque underflowd
>>>>>>> 43226de5cf36477b696c497118d42473a8c97f8a
        ;
}

void deque_print(deque self)
{
    printf("size is %d\n", self->size);
    for (int i = 0; i <= self->size; i++)
        printf(" %d", self->array[i]);
    printf("\n");
    printf("front is %d,  back is %d\n", self->front, self->back);
}
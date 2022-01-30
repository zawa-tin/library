#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct queue_entity
{
    int size;
    int head;
    int tail;
    int *array;
};
typedef struct queue_entity *queue;

queue queue_constructor(queue self, int size)
{
    self = (queue)malloc(sizeof(struct queue_entity));
    self->size = size;
    self->head = 0;
    self->tail = 0;
    self->array = (int *)malloc(sizeof(int) * (size + 1));

    return self;
}

void queue_destructor(queue self)
{
    self->head = self->tail = self->size = 0;
    free(self->array);
    free(self);
}

bool is_queue_empty(queue self)
{
    if (self->head == self->tail)
        return true;
    else
        return false;
}

bool is_queue_full(queue self)
{
    if ((self->head == self->tail + 1) || (self->head == 0 && self->tail == self->size))
        return true;
    else
        return false;
}

void queue_enqueue(queue self, int value)
{
    if (!is_queue_full(self))
    {
        self->array[self->tail] = value;
        if (self->tail == self->size)
            self->tail = 0;
        else
            self->tail++;
    }
    else
        // queue overflow
        ;
}

int queue_dequeue(queue self)
{
    if (!is_queue_empty(self))
    {
        int dequeued_value = self->array[self->head];
        if (self->head == self->size)
            self->head = 0;
        else
            self->head++;

        return dequeued_value;
    }
    else
        // queue underflow
        ;
}

int queue_front(queue self)
{
    if (!is_queue_empty(self))
        return self->array[self->head];
    else
        // queue underflow
        ;
}

// for debug
void queue_print(queue self)
{
    printf("size = %d\n", self->size);
    for (int i = 0; i < self->size + 1; i++)
        printf(" %d", self->array[i]);
    printf("\n");
    printf("head = %d(value is %d), tail = %d\n", self->head, self->array[self->head], self->tail);
}
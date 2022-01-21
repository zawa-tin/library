#include <stdio.h>
#include <stdlib.h>

struct queue_entity {
    int size;
    int head;
    int tail;
    int *array;
};
typedef struct queue_entity * queue;

queue queue_constructor(queue self, int size) {
    self = (queue)malloc(sizeof(struct queue_entity));
    self->size = size;
    self->head = 0;
    self->tail = 0;
    self->array = (int *)malloc(sizeof(int) * (size + 1));
}

queue queue_destructor(queue self) {
    self->head = self->tail = self->size = 0;
    free(self->array);
    free(self);
}
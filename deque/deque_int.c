#include <stdio.h>
#include <stdlib.h>

struct deque_entity {
    int front;
    int back;
    int size;
    int *array;
};
typedef struct deque_entity *deque;

deque deque_constructor(deque self, int size) {
    self = (deque)malloc(sizeof(struct deque_entity));
    self->array = (int *)malloc(sizeof(int) * (size + 1));
    self->front = (size + 1) / 2;
    self->back = self->front + 1;
    self->size = size;

    return self;
}

deque deque_destructor(deque self) {
    self->front = self->back = self->size = 0;
    free(self->array);
    free(self);
}
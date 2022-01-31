#include <stdio.h>
#include <stdlib.h>

struct vector_entity
{
    int *vec;
    int size;
    int capacity;
};
typedef struct vector_entity *vector;

vector vector_construct(vector self, int n)
{
    self = (vector)malloc(sizeof(vector));

    int capacity = 1;
    while (capacity <= n)
        capacity *= 2;

    self->capacity = capacity;
    self->size = n;
    self->vec = (int *)malloc(sizeof(int) * capacity);

    return self;
}

void vector_destruct(vector const self)
{
    free(self->vec);
    free(self);
}

void vector_resize(vector const self, int new_size)
{
    int *new = (int *)realloc(self->vec, sizeof(int) * new_size);
    self->vec = new;
    self->capacity = new_size;
}

void vector_insert(vector self, int value, int index)
{
    if (index >= self->capacity)
    {
        int capacity = self->capacity;
        while (capacity <= index)
            capacity *= 2;

        vector_resize(self, capacity);
    }

    if (index >= self->size)
    {
        self->size = index + 1;
    }

    self->vec[index] = value;
}

int vector_erase(vector const self, int index)
{
    if (index >= self->size)
        return 0;

    int erased_value = self->vec[index];

    if (index >= self->size / 2)
    {
        for (int i = index; i < self->size - 1; i++)
            self->vec[i] = self->vec[i + 1];
        self->size--;
    }
    else
    {
        for (int i = index; i > 0; i--)
            self->vec[i] = self->vec[i - 1];
        self->vec = &self->vec[1];
        self->size--;
    }

    return erased_value;
}

void vector_push_back(vector const self, int value)
{
    vector_insert(self, value, self->size);
}

int vector_pop_back(vector const self)
{
    int poped_value;
    if (self->size > 0)
        poped_value = vector_erase(self, self->size - 1);
    else
        return -1;

    return poped_value;
}

void vector_clear(vector const self)
{
    free(self->vec);
    self->size = 0;
    self->capacity = 1;
    self->vec = (int *)malloc(sizeof(int) * self->capacity);
}

// for debug
void vector_print(vector const self)
{
    for (int i = 0; i < self->size; i++)
        printf(" %d", self->vec[i]);
    printf("\n");
    printf("size is %d\n", self->size);
    printf("capacity is %d\n", self->capacity);
}
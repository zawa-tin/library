#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *vec;
    int size;
    int capacity;
}vector;

vector * construct_vector(int n) {
    vector* const this = (vector *)malloc(sizeof(vector));

    int capacity = 1;
    while (capacity <= n)
        capacity *= 2;
    
    this->capacity = capacity;
    this->size = n;
    this->vec = (int *)malloc(sizeof(int) * capacity);

    return this;
}

destruct_vector(vector* const this) {
    free(this->vec);
    free(this);
}

void resize(vector* const this, int new_size) {
    int *new = (int *)realloc(this->vec, sizeof(int) * new_size);
    this->vec = new;
    this->capacity = new_size;
}

void insert(vector* const this, int value, int index) {
    if (index >= this->capacity) {
        int capacity = this->capacity;
        while (capacity <= index)
            capacity *= 2;
        
        resize(this, capacity);
    }

    if (index >= this->size) {
        this->size = index + 1;
    }

    this->vec[index] = value;
}

int erase(vector* const this, int index) {
    if (index >= this->size)
        return 0;
    
    int erased_value = this->vec[index];
    
    if (index >= this->size / 2) {
        for (int i = index ; i < this->size - 1 ; i++)
            this->vec[i] = this->vec[i + 1];
        this->size--;
    }
    else {
        for (int i = index ; i > 0 ; i--)
            this->vec[i] = this->vec[i - 1];
        this->vec = &this->vec[1];
        this->size--;
    }

    return erased_value;
}

void push_back(vector* const this, int value) {
    insert(this, value, this->size);
}

int pop_back(vector* const this) {
    int poped_value;
    if (this->size > 0)
        poped_value = erase(this, this->size - 1);
    else
        return -1;
        
    return poped_value;
}

// for debug
void print_vector(vector* const this) {
    for (int i = 0 ; i < this->size ; i++)
        printf(" %d", this->vec[i]);
    printf("\n");
    printf("size is %d\n", this->size);
    printf("capacity is %d\n", this->capacity);
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *vec;
    int size;
}vector;

void construct(vector* const this, int n) {
    this->vec = (int *)malloc(sizeof(int) * n);
    this->size = n;
}

void resize(vector* const this, int new_size) {
    int *new = (int *)realloc(this->vec, sizeof(int) * new_size);
    this->vec = new;
    this->size = new_size;
}

void insert(vector* const this, int value, int index) {
    if (index >= this->size)
        resize(this, index + 1);
    this->vec[index] = value;
}

int erase(vector* const this, int index) {
    if (index >= this->size)
        return 0;
    
    int erased_value = this->vec[index];
    
    for (int i = index ; i < this->size - 1 ; i++)
        this->vec[i] = this->vec[i + 1];
    
    resize(this, this->size - 1);

    return erased_value;
}

void push_back(vector* const this, int value) {
    resize(this, this->size + 1);

    insert(this, value, this->size - 1);
}

int pop_back(vector* const this) {
    int poped_value;
    if (this->size > 0)
        poped_value = erase(this, this->size - 1);
    else
        return -1;
        
}
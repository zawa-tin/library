#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * vec;
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

void insert(vector* const this, int value, int place) {
    if (place >= this->size)
        resize(this, place + 1);
    this->vec[place] = value;
}

int erase(vector* const this, int place) {
    if (place >= this->size)
        return 0;
    
    int erased_value = this->vec[place];
    
    for (int i = place ; i < this->size - 1 ; i++)
        this->vec[i] = this->vec[i + 1];
    
    resize(this, this->size - 1);

    return erased_value;
}

void pushback(vector* const this, int value) {
    resize(this, this->size + 1);

    insert(this, value, this->size - 1);
}

int popback(vector* const this) {
    int poped_value;
    if (this->size > 0)
        poped_value = erase(this, this->size - 1);
    else
        return -1;
        
}
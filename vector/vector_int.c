#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *vec;
    int size;
    int capacity;
}vector;

void construct(vector* const this, int n) {
    int capacity = 1;
    while (capacity <= n)
        capacity *= 2;
    
    this->capacity = capacity;
    this->size = n;
    this->vec = (int *)malloc(sizeof(int) * capacity);
}

void resize(vector* const this, int new_size) {
    int *new = (int *)realloc(this->vec, sizeof(int) * new_size);
    this->vec = new;
    this->size = new_size;
}

void insert(vector* const this, int value, int index) {
    if (index >= this->capacity) {
        int capacity;
        // for (capacity = this->capacity ; capacity <= index ; capacity *= 2)
        //     ;
        while (capacity <= index)
            capacity *= 2;
        
        resize(this, capacity);
        this->capacity = capacity;
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
    
    for (int i = index ; i < this->size - 1 ; i++)
        this->vec[i] = this->vec[i + 1];
    
    resize(this, this->size - 1);

    return erased_value;
}

void push_back(vector* const this, int value) {
    insert(this, value, this->size - 1);
}

int pop_back(vector* const this) {
    int poped_value;
    if (this->size > 0)
        poped_value = erase(this, this->size - 1);
    else
        return -1;
        
}

int main() {
    vector hoge;
    construct(&hoge, 3);

    insert(&hoge, 7, 2);
    printf("%d\n", hoge.vec[2]);
    printf("%d\n", hoge.capacity);
}
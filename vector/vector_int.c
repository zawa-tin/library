#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int * vec;
    int size;
    int max_size;
    int empty;
    int begin;
    int end;
}vector;

void construct(vector* const this, int n) {
    this->vec = (int *)malloc(sizeof(int) * n);
    this->size = n;
    this->empty = 1;
    this->begin = INT_MAX;
    this->end = -1;
}

void insert(vector* const this, int value, int place) {
    if (place >= this->size)
        exit(8); //適当
    this->vec[place] = value;

    if (place < this->begin)
        this->begin = place;

    if (place > this->end)
        this->end = place;
}

void resize(vector* const this, int new_size) {
    (int *)realloc(this, sizeof(new_size));
    this->size = new_size;
}

int main() {

    vector sample;
    construct(&sample, 5);

    insert(&sample, 3, 1);
}
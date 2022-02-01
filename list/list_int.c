#include <stdio.h>
#include <stdlib.h>

typedef struct node_entity *node;
struct node_entity
{
    int key;
    node next;
    node prev;
};

struct list_entity
{
    node head;
    node tail;
    int size;
};
typedef struct list_entity *list;

list list_constructor(list self)
{
    self = (list)malloc(sizeof(struct list_entity));
    self->size = 0;
    return self;
}

void list_destructor(list self)
{
    free(self->head);
    free(self->tail);
    free(self);
}

node list_make_node()
{
    node new_node = (node)malloc(sizeof(struct node_entity));
    return new_node;
}

node list_assign_value(node new_node, int value)
{
    new_node->key = value;
    return new_node;
}
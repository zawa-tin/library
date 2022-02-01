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
};
typedef struct list_entity *list;

list list_constructor(list self)
{
    self = (list)malloc(sizeof(struct list_entity));
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

void list_insert_head(list self, int key)
{
    node new_node = list_assign_value(list_make_node(), key);
    // when list has no nodes
    if (self->head == NULL)
    {
        self->head = new_node;
        self->tail = new_node;
    }
    // when list has nodes
    else
    {
        new_node->next = self->head;
        self->head->prev = new_node;
        self->head = new_node;
    }
}

void list_insert_tail(list self, int value)
{
    node new_node = list_assign_value(list_make_node(), value);
    // when list has no nodes
    if (self->tail == NULL)
    {
        self->tail = new_node;
        self->head = new_node;
    }
    // when list has nodes
    else
    {
        new_node->prev = self->tail;
        self->tail->next = new_node;
        self->tail = new_node;
    }
}

// insert in front of iterator
void list_insert(list self, node iterator, int value)
{
    node new_node = list_assign_value(list_make_node(), value);
    // when iterator node is head
    if (iterator->prev == NULL)
    {
        new_node->next = iterator;
        iterator->prev = new_node;
        self->head = new_node;
    }
    // when iterator node is not head
    else
    {
        new_node->next = iterator;
        new_node->prev = iterator->prev;
        iterator->prev->next = new_node;
        iterator->prev = new_node;
    }
}
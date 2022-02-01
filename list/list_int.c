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

    self->size++;
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

    self->size++;
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

    self->size++;
}

void list_delete_head(list self)
{
    // when list has not node
    if (self->head == NULL)
        return;

    node delete_node = self->head;

    // when list has only delete_node
    if (delete_node->next == NULL)
    {
        self->head = NULL;
        self->tail = NULL;
    }
    // when list has multiple nodes
    else
    {
        self->head = delete_node->next;
        delete_node->next->prev = NULL;
    }

    self->size--;

    free(delete_node);
}

void list_delete_tail(list self)
{
    // when list has not node
    if (self->tail == NULL)
        return;

    node delete_node = self->tail;

    // when list has only delete_node
    if (delete_node->prev == NULL)
    {
        self->tail = NULL;
        self->head = NULL;
    }
    // when list has multiple nodes
    else
    {
        self->tail = delete_node->prev;
        delete_node->prev->next = NULL;
    }

    self->size--;

    free(delete_node);
}

void list_delete(list self, node iterator)
{
    if (iterator == NULL)
    {
        // something wrong...
        return;
    }

    node delete_node = iterator;
    // when delete_node is head
    if (delete_node->prev = NULL)
    {
        list_delete_head(self);
        return;
    }
    // when delete_node is tail
    else if (delete_node->next == NULL)
    {
        list_delete_tail(self);
        return;
    }

    delete_node->next->prev = delete_node->prev;
    delete_node->prev->next = delete_node->next;

    self->size--;

    free(delete_node);
}

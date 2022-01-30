#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONCATENATE(x, y) x##y
#define CONCAT(x, y) CONCATENATE(x, y)

#define QUEUE_TYPE(T) \
    CONCAT(queue, T)
#define QUEUE_REF(T) \
    CONCAT(queue_ref, T)

#define DEFINE_QUEUE(T)  \
    struct QUEUE_TYPE(T) \
    {                    \
        int size;        \
        int head;        \
        int tail;        \
        T *array;        \
    };                   \
    typedef struct QUEUE_TYPE(T) * QUEUE_REF(T);

#define QUEUE_METHOD(T, f) \
    CONCAT(QUEUE_TYPE(T), f)

#define DEFINE_QUEUE_CONSTRUCTOR(T)                                \
    QUEUE_REF(T)                                                   \
    QUEUE_METHOD(T, constructor)                                   \
    (QUEUE_REF(T) self, int size)                                  \
    {                                                              \
        self = (QUEUE_REF(T))malloc(sizeof(struct QUEUE_TYPE(T))); \
        self->size = size;                                         \
        self->head = 0;                                            \
        self->tail = 0;                                            \
        self->array = (T *)malloc(sizeof(T) * (size + 1));         \
                                                                   \
        return self;                                               \
    }

#define DEFINE_QUEUE_DESTRUCTOR(T)                      \
    void QUEUE_METHOD(T, destructor)(QUEUE_REF(T) self) \
    {                                                   \
        self->head = 0;                                 \
        self->tail = 0;                                 \
        self->size = 0;                                 \
        free(self->array);                              \
        free(self);                                     \
    }

#define DEFINE_IS_QUEUE_EMPTY(T)                      \
    bool QUEUE_METHOD(T, is_empty)(QUEUE_REF(T) self) \
    {                                                 \
        if (self->head == self->tail)                 \
            return true;                              \
        else                                          \
            return false;                             \
    }

#define DEFINE_IS_QUEUE_FULL(T)                                                              \
    bool QUEUE_METHOD(T, is_full)(QUEUE_REF(T) self)                                         \
    {                                                                                        \
        if ((self->head == self->tail + 1) || (self->head == 0 && self->tail == self->size)) \
            return true;                                                                     \
        else                                                                                 \
            return false;                                                                    \
    }

#define DEFINE_QUEUE_ENQUEUE(T)                               \
    void QUEUE_METHOD(T, enqueue)(QUEUE_REF(T) self, T value) \
    {                                                         \
        if (!QUEUE_METHOD(T, is_full)(self))                  \
        {                                                     \
            self->array[self->tail] = value;                  \
            if (self->tail == self->size)                     \
                self->tail = 0;                               \
            else                                              \
                self->tail++;                                 \
        }                                                     \
        else                                                  \
            ;                                                 \
    }

#define DEFINE_QUEUE_DEQUEUE(T)                         \
    T QUEUE_METHOD(T, dequeue)(QUEUE_REF(T) self)       \
    {                                                   \
        if (!QUEUE_METHOD(T, is_empty)(self))           \
        {                                               \
            T dequeued_value = self->array[self->head]; \
            if (self->head == self->size)               \
                self->head = 0;                         \
            else                                        \
                self->head++;                           \
                                                        \
            return dequeued_value;                      \
        }                                               \
        else                                            \
            ;                                           \
    }

#define DEFINE_QUEUE_FRONT(T)                   \
    T QUEUE_METHOD(T, front)(QUEUE_REF(T) self) \
    {                                           \
        if (!QUEUE_METHOD(T, is_empty)(self))   \
            return self->array[self->head];     \
        else                                    \
            ;                                   \
    }

// for debug
// You have to change format identifier if you use this function.
#define DEFINE_QUEUE_PRINT(T)                                                                            \
    void QUEUE_METHOD(T, print)(QUEUE_REF(T) self)                                                       \
    {                                                                                                    \
        for (int i = 0; i < self->size + 1; i++)                                                         \
            printf(" %lf", self->array[i]);                                                              \
        printf("\n");                                                                                    \
        printf("head = %d(value is %lf), tail = %d\n", self->head, self->array[self->head], self->tail); \
    }

#define DEFINE_QUEUE_METHOD(T)  \
    DEFINE_QUEUE_CONSTRUCTOR(T) \
    DEFINE_QUEUE_DESTRUCTOR(T)  \
    DEFINE_IS_QUEUE_EMPTY(T)    \
    DEFINE_IS_QUEUE_FULL(T)     \
    DEFINE_QUEUE_ENQUEUE(T)     \
    DEFINE_QUEUE_DEQUEUE(T)     \
    DEFINE_QUEUE_FRONT(T)       \
    DEFINE_QUEUE_PRINT(T)
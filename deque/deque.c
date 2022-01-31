#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONCATENATE(x, y) x##y
#define CONCAT(x, y) CONCATENATE(x, y)

#define DEQUE_TYPE(T) \
    CONCAT(deque, T)
#define DEQUE_REF(T) \
    CONCAT(deque_ref, T)

#define DEFINE_DEQUE(T)  \
    struct DEQUE_TYPE(T) \
    {                    \
        int front;       \
        int back;        \
        int size;        \
        T *array;        \
    };                   \
    typedef struct DEQUE_TYPE(T) * DEQUE_REF(T);

#define DEQUE_METHOD(T, f) \
    CONCAT(DEQUE_TYPE(T), f)

#define DEFINE_DEQUE_CONSTRUCTOR(T)                                \
    DEQUE_REF(T)                                                   \
    DEQUE_METHOD(T, constructor)                                   \
    (DEQUE_REF(T) self, int size)                                  \
    {                                                              \
        self = (DEQUE_REF(T))malloc(sizeof(struct DEQUE_TYPE(T))); \
        self->array = (T *)malloc(sizeof(T) * (size + 1));         \
        self->front = (size + 1) / 2;                              \
        self->back = self->front + 1;                              \
        self->size = size;                                         \
                                                                   \
        return self;                                               \
    }

#define DEFINE_DEQUE_DESTRUCTOR(T)                      \
    void DEQUE_METHOD(T, destructor)(DEQUE_REF(T) self) \
    {                                                   \
        self->front = 0;                                \
        self->back = 0;                                 \
        self->size = 0;                                 \
        free(self->array);                              \
        free(self);                                     \
    }

#define DEFINE_IS_DEQUE_EMPTY(T)                                                             \
    bool DEQUE_METHOD(T, is_empty)(DEQUE_REF(T) self)                                        \
    {                                                                                        \
        if (self->front + 1 == self->back || (self->back == 0 && self->front == self->size)) \
            return true;                                                                     \
        else                                                                                 \
            return false;                                                                    \
    }

#define DEFINE_IS_DEQUE_FULL(T)                      \
    bool DEQUE_METHOD(T, is_full)(DEQUE_REF(T) self) \
    {                                                \
        if (self->front == self->back)               \
            return true;                             \
        else                                         \
            return false;                            \
    }

#define DEFINE_DEQUE_PUSH_FRONT(T)                               \
    void DEQUE_METHOD(T, push_front)(DEQUE_REF(T) self, T value) \
    {                                                            \
        if (!DEQUE_METHOD(T, is_full)(self))                     \
        {                                                        \
            self->array[self->front] = value;                    \
            if (self->front == 0)                                \
                self->front = self->size;                        \
            else                                                 \
                self->front--;                                   \
        }                                                        \
        else                                                     \
            ;                                                    \
    }

#define DEFINE_DEQUE_PUSH_BACK(T)                               \
    void DEQUE_METHOD(T, push_back)(DEQUE_REF(T) self, T value) \
    {                                                           \
        if (!DEQUE_METHOD(T, is_full)(self))                    \
        {                                                       \
            self->array[self->back] = value;                    \
            if (self->back == self->size)                       \
                self->back = 0;                                 \
            else                                                \
                self->back++;                                   \
        }                                                       \
        else                                                    \
            ;                                                   \
    }

#define DEFINE_DEQUE_POP_FRONT(T)                   \
    T DEQUE_METHOD(T, pop_front)(DEQUE_REF(T) self) \
    {                                               \
        if (!DEQUE_METHOD(T, is_empty)(self))       \
        {                                           \
            if (self->front == self->size)          \
                self->front = 0;                    \
            else                                    \
                self->front++;                      \
                                                    \
            return self->array[self->front];        \
        }                                           \
        else                                        \
            ;                                       \
    }

#define DEFINE_DEQUE_POP_BACK(T)                   \
    T DEQUE_METHOD(T, pop_back)(DEQUE_REF(T) self) \
    {                                              \
        if (!DEQUE_METHOD(T, is_empty)(self))      \
        {                                          \
            if (self->back == 0)                   \
                self->back = self->size;           \
            else                                   \
                self->back--;                      \
                                                   \
            return self->array[self->back];        \
        }                                          \
        else                                       \
            ;                                      \
    }

// for debug
// You have to change format identifier if you use this function.
#define DEFINE_DEQUE_PRINT(T)                                          \
    void DEQUE_METHOD(T, print)(DEQUE_REF(T) self)                     \
    {                                                                  \
        printf("size is %d\n", self->size);                            \
        for (int i = 0; i < self->size + 1; i++)                       \
            printf(" %d", self->array[i]);                             \
        printf("\n");                                                  \
        printf("front is %d,  back is %d\n", self->front, self->back); \
    }

#define DEFINE_DEQUE_METHOD(T)  \
    DEFINE_DEQUE_CONSTRUCTOR(T) \
    DEFINE_DEQUE_DESTRUCTOR(T)  \
    DEFINE_IS_DEQUE_EMPTY(T)    \
    DEFINE_IS_DEQUE_FULL(T)     \
    DEFINE_DEQUE_PUSH_FRONT(T)  \
    DEFINE_DEQUE_PUSH_BACK(T)   \
    DEFINE_DEQUE_POP_FRONT(T)   \
    DEFINE_DEQUE_POP_BACK(T)    \
    DEFINE_DEQUE_PRINT(T)

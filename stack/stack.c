#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONCATENATE(x, y) x##y
#define CONCAT(x, y) CONCATENATE(x, y)

#define STACK_TYPE(T) \
    CONCAT(stack, T)
#define STACK_REF(T) \
    CONCAT(stack_ref, T)

#define DEFINE_STACK(T)  \
    struct STACK_TYPE(T) \
    {                    \
        T *array;        \
        int size;        \
        int top;         \
    };                   \
    typedef struct STACK_TYPE(T) * STACK_REF(T);

#define STACK_METHOD(T, f) \
    CONCAT(STACK_TYPE(T), f)

#define DEFINE_STACK_CONSTRUCTOR(T)                                \
    STACK_REF(T)                                                   \
    STACK_METHOD(T, constructor)                                   \
    (STACK_REF(T) self, int size)                                  \
    {                                                              \
        self = (STACK_REF(T))malloc(sizeof(struct STACK_TYPE(T))); \
        self->size = size;                                         \
        self->top = 0;                                             \
        self->array = (T *)malloc(sizeof(T) * (size + 1));         \
                                                                   \
        return self;                                               \
    }

#define DEFINE_STACK_DESTRUCTOR(T)                      \
    void STACK_METHOD(T, destructor)(STACK_REF(T) self) \
    {                                                   \
        self->size = 0;                                 \
        self->top = 0;                                  \
        free(self->array);                              \
        free(self);                                     \
    }

#define DEFINE_IS_STACK_EMPTY(T)                      \
    bool STACK_METHOD(T, is_empty)(STACK_REF(T) self) \
    {                                                 \
        if (self->top == 0)                           \
            return true;                              \
        else                                          \
            return false;                             \
    }

#define DEFINE_IS_STACK_FULL(T)                      \
    bool STACK_METHOD(T, is_full)(STACK_REF(T) self) \
    {                                                \
        if (self->top == self->size)                 \
            return true;                             \
        else                                         \
            return false;                            \
    }

#define DEFINE_STACK_PUSH(T)                               \
    void STACK_METHOD(T, push)(STACK_REF(T) self, T value) \
    {                                                      \
        if (!STACK_METHOD(T, is_full)(self))               \
        {                                                  \
            self->top++;                                   \
            self->array[self->top] = value;                \
        }                                                  \
        else                                               \
            ;                                              \
    }

#define DEFINE_STACK_POP(T)                    \
    T STACK_METHOD(T, pop)(STACK_REF(T) self)  \
    {                                          \
        if (!STACK_METHOD(T, is_empty)(self))  \
        {                                      \
            self->top--;                       \
            return self->array[self->top + 1]; \
        }                                      \
        else                                   \
            ;                                  \
    }

#define DEFINE_STACK_TOP(T)                   \
    T STACK_METHOD(T, top)(STACK_REF(T) self) \
    {                                         \
        if (!STACK_METHOD(T, is_empty)(self)) \
            return self->array[self->top];    \
        else                                  \
            ;                                 \
    }

// for debug
// You have to change format identifier if you use this function.
#define DEFINE_STACK_PRINT(T)                                                  \
    void STACK_METHOD(T, print)(STACK_REF(T) self)                             \
    {                                                                          \
        for (int i = 0; i < self->size + 1; i++)                               \
            printf(" %d", self->array[i]);                                     \
        printf("\n");                                                          \
        printf("top is %d (value = %d)\n", self->top, self->array[self->top]); \
    }

#define DEFINE_STACK_METHOD(T)  \
    DEFINE_STACK_CONSTRUCTOR(T) \
    DEFINE_STACK_DESTRUCTOR(T)  \
    DEFINE_IS_STACK_EMPTY(T)    \
    DEFINE_IS_STACK_FULL(T)     \
    DEFINE_STACK_PUSH(T)        \
    DEFINE_STACK_POP(T)         \
    DEFINE_STACK_TOP(T)         \
    DEFINE_STACK_PRINT(T)
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
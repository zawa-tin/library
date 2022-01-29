#include <stdio.h>
#include <stdlib.h>

#define CONCATENATE(x, y) x##y
#define CONCAT(x, y) CONCATENATE(x, y)

#define VECTOR_TYPE(T) \
    CONCAT(vector, T)
#define VECTOR_REF(T) \
    CONCAT(vector_ref, T)

#define DEFINE_VECTOR(T)  \
    struct VECTOR_TYPE(T) \
    {                     \
        T *vec;           \
        int size;         \
        int capacity;     \
    };                    \
    typedef struct VECTOR_TYPE(T) * VECTOR_REF(T);

#define VECTOR_METHOD(T, f) \
    CONCAT(VECTOR_TYPE(T), f)

#define DEFINE_VECTOR_CONSTRUCTOR(T)                                 \
    VECTOR_REF(T)                                                    \
    VECTOR_METHOD(T, constructor)                                    \
    (VECTOR_REF(T) self, int n)                                      \
    {                                                                \
                                                                     \
        self = (VECTOR_REF(T))malloc(sizeof(struct VECTOR_TYPE(T))); \
                                                                     \
        int capacity = 1;                                            \
        while (capacity <= n)                                        \
            capacity *= 2;                                           \
                                                                     \
        self->capacity = capacity;                                   \
        self->size = n;                                              \
        self->vec = (T *)malloc(sizeof(T) * capacity);               \
                                                                     \
        return self;                                                 \
    }

#define DEFINE_VECTOR_DESTRUCTOR(T)                             \
    void VECTOR_METHOD(T, destructor)(VECTOR_REF(T) const self) \
    {                                                           \
        free(self->vec);                                        \
        free(self);                                             \
    }

#define DEFINE_VECTOR_RESIZE(T)                                           \
    void VECTOR_METHOD(T, resize)(VECTOR_REF(T) const self, int new_size) \
    {                                                                     \
        T *new = (T *)realloc(self->vec, sizeof(T) * new_size);           \
        self->vec = new;                                                  \
        self->capacity = new_size;                                        \
    }

#define DEFINE_VECTOR_INSERT(T)                                                 \
    void VECTOR_METHOD(T, insert)(VECTOR_REF(T) const self, T value, int index) \
    {                                                                           \
        if (index >= self->capacity)                                            \
        {                                                                       \
            int capacity = self->capacity;                                      \
            while (capacity <= index)                                           \
                capacity *= 2;                                                  \
                                                                                \
            VECTOR_METHOD(T, resize)                                            \
            (self, capacity);                                                   \
        }                                                                       \
                                                                                \
        if (index >= self->size)                                                \
        {                                                                       \
            self->size = index + 1;                                             \
        }                                                                       \
                                                                                \
        self->vec[index] = value;                                               \
    }

#define DEFINE_VECTOR_ERASE(T)                                     \
    T VECTOR_METHOD(T, erase)(VECTOR_REF(T) const self, int index) \
    {                                                              \
        if (index >= self->size)                                   \
            return 0;                                              \
                                                                   \
        T erased_value = self->vec[index];                         \
                                                                   \
        if (index >= self->size / 2)                               \
        {                                                          \
            for (int i = index; i < self->size - 1; i++)           \
                self->vec[i] = self->vec[i + 1];                   \
            self->size--;                                          \
        }                                                          \
        else                                                       \
        {                                                          \
            for (int i = index; i > 0; i--)                        \
                self->vec[i] = self->vec[i - 1];                   \
            self->vec = &self->vec[1];                             \
            self->size--;                                          \
        }                                                          \
                                                                   \
        return erased_value;                                       \
    }

#define DEFINE_VECTOR_PUSH_BACK(T)                                      \
    void VECTOR_METHOD(T, push_back)(VECTOR_REF(T) const self, T value) \
    {                                                                   \
        VECTOR_METHOD(T, insert)                                        \
        (self, value, self->size);                                      \
    }

#define DEFINE_VECTOR_POPBACK(T)                                  \
    T VECTOR_METHOD(T, pop_back)(VECTOR_REF(T) const self)        \
    {                                                             \
        T poped_value;                                            \
        if (self->size > 0)                                       \
            return VECTOR_METHOD(T, erase)(self, self->size - 1); \
        else                                                      \
            return -1;                                            \
                                                                  \
        return poped_value;                                       \
    }

// for debug
// You have to change format identifier if you use this function.
#define DEFINE_VECTOR_PRINT(T)                             \
    void VECTOR_METHOD(T, print)(VECTOR_REF(T) const self) \
    {                                                      \
        for (int i = 0; i < self->size; i++)               \
            printf(" %f", self->vec[i]);                   \
        printf("\n");                                      \
        printf("size is %d\n", self->size);                \
        printf("capacity is %d\n", self->capacity);        \
    }

#define DEFINE_VECTOR_METHODS(T) \
    DEFINE_VECTOR_CONSTRUCTOR(T) \
    DEFINE_VECTOR_DESTRUCTOR(T)  \
    DEFINE_VECTOR_RESIZE(T)      \
    DEFINE_VECTOR_INSERT(T)      \
    DEFINE_VECTOR_ERASE(T)       \
    DEFINE_VECTOR_PUSH_BACK(T)   \
    DEFINE_VECTOR_POPBACK(T)     \
    DEFINE_VECTOR_PRINT(T)
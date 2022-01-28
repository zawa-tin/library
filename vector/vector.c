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

#define DEFINE_VECTOR_CONSTRUCTOR(T)                                       \
    VECTOR_REF(T)                                                          \
    VECTOR_METHOD(T, constructor)(int n)                                   \
    {                                                                      \
                                                                           \
        VECTOR_REF(T)                                                      \
        const this = (VECTOR_REF(T))malloc(sizeof(struct VECTOR_TYPE(T))); \
                                                                           \
        int capacity = 1;                                                  \
        while (capacity <= n)                                              \
            capacity *= 2;                                                 \
                                                                           \
        this->capacity = capacity;                                         \
        this->size = n;                                                    \
        this->vec = (T *)malloc(sizeof(T) * capacity);                     \
                                                                           \
        return this;                                                       \
    }

#define DEFINE_VECTOR_DESTRUCTOR(T)                             \
    void VECTOR_METHOD(T, destructor)(VECTOR_REF(T) const this) \
    {                                                           \
        free(this->vec);                                        \
        free(this);                                             \
    }

#define DEFINE_VECTOR_RESIZE(T)                                           \
    void VECTOR_METHOD(T, resize)(VECTOR_REF(T) const this, int new_size) \
    {                                                                     \
        T *new = (T *)realloc(this->vec, sizeof(T) * new_size);           \
        this->vec = new;                                                  \
        this->capacity = new_size;                                        \
    }

#define DEFINE_VECTOR_INSERT(T)                                                 \
    void VECTOR_METHOD(T, insert)(VECTOR_REF(T) const this, T value, int index) \
    {                                                                           \
        if (index >= this->capacity)                                            \
        {                                                                       \
            int capacity = this->capacity;                                      \
            while (capacity <= index)                                           \
                capacity *= 2;                                                  \
                                                                                \
            VECTOR_METHOD(T, resize)                                            \
            (this, capacity);                                                   \
        }                                                                       \
                                                                                \
        if (index >= this->size)                                                \
        {                                                                       \
            this->size = index + 1;                                             \
        }                                                                       \
                                                                                \
        this->vec[index] = value;                                               \
    }

#define DEFINE_VECTOR_ERASE(T)                                     \
    T VECTOR_METHOD(T, erase)(VECTOR_REF(T) const this, int index) \
    {                                                              \
        if (index >= this->size)                                   \
            return 0;                                              \
                                                                   \
        T erased_value = this->vec[index];                         \
                                                                   \
        if (index >= this->size / 2)                               \
        {                                                          \
            for (int i = index; i < this->size - 1; i++)           \
                this->vec[i] = this->vec[i + 1];                   \
            this->size--;                                          \
        }                                                          \
        else                                                       \
        {                                                          \
            for (int i = index; i > 0; i--)                        \
                this->vec[i] = this->vec[i - 1];                   \
            this->vec = &this->vec[1];                             \
            this->size--;                                          \
        }                                                          \
                                                                   \
        return erased_value;                                       \
    }

#define DEFINE_VECTOR_PUSH_BACK(T)                                      \
    void VECTOR_METHOD(T, push_back)(VECTOR_REF(T) const this, T value) \
    {                                                                   \
        VECTOR_METHOD(T, insert)                                        \
        (this, value, this->size);                                      \
    }

#define DEFINE_VECTOR_POPBACK(T)                                  \
    T VECTOR_METHOD(T, pop_back)(VECTOR_REF(T) const this)        \
    {                                                             \
        T poped_value;                                            \
        if (this->size > 0)                                       \
            return VECTOR_METHOD(T, erase)(this, this->size - 1); \
        else                                                      \
            return -1;                                            \
                                                                  \
        return poped_value;                                       \
    }

// for debug
// You have to change format identifier if you use this function.
#define DEFINE_VECTOR_PRINT(T)                             \
    void VECTOR_METHOD(T, print)(VECTOR_REF(T) const this) \
    {                                                      \
        for (int i = 0; i < this->size; i++)               \
            printf(" %f", this->vec[i]);                   \
        printf("\n");                                      \
        printf("size is %d\n", this->size);                \
        printf("capacity is %d\n", this->capacity);        \
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

int main()
{
}
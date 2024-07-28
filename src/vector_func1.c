#include "socket.h"

void vector_set(struct Vector *vector, size_t idx, void *element)
{
    assert(vector != NULL);
    assert(idx < vector->length);

    memcpy(&((char *)vector->data)[idx * vector->elem_size], element,
        vector->elem_size);
}

void vector_clear(struct Vector *vector)
{
    assert(vector != NULL);

    vector->length = 0;
}

void *vector_data(struct Vector *vector)
{
    assert(vector != NULL);

    return (vector->data);
}

size_t vector_length(struct Vector *vector)
{
    assert(vector != NULL);

    return (vector->length);
}

size_t vector_capacity(struct Vector *vector)
{
    assert(vector != NULL);

    return vector->capacity;
}

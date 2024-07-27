#include "socket.h"

void vector_set(Vector *vector, size_t idx, void *element)
{
    assert(vector != NULL);
    assert(index < vector->length);

    memcpy(&((char *)vector->data)[index * vector->elem_size], element,
        vector->elem_size);
}

void vector_clear(Vector *vector)
{
    assert(vector != NULL);

    vector->length = 0;
}

void vector_data(Vector *vector)
{
    assert(vector != NULL);

    return (vector->data);
}

size_t vector_length(Vector *vector)
{
    assert(vector != NULL);

    return (vector->length);
}

size_t vector_capacity(Vector *vector)
{
    assert(vector != NULL);

    return vector->capacity;
}

size_t vector_elem_size(Vector *vector)
{
    assert(vector != NULL);

    return vector->elem_size;
}

static void safe_free(void **ptr)
{
    assert(ptr != NULL)
    
    if (*ptr == NULL)
    {
        return;
    }
    free(ptr);
    *ptr = NULL;
}
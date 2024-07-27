#include "socket.h"


Vector *vector_init(size_t elem_size, size_t capacity)
{
    assert(elem_size > 0);

    struct Vector *vector = malloc(sizeof(struct Vector));
    if (vector == NULL)
    {
        return (NULL);
    }
    if (capacity == 0)
    {
        capacity = VECTOR_CAP;
    }
    vector->data = malloc(elem_size * capacity);
    if (vector->data == NULL)
    {
        free(vector);
        return (NULL);
    }

    vector->length = 0;
    vector->capacity = capacity;
    vector->elem_size = elem_size;

    return (vector);
}


void vector_free(struct vector *vector, void *element)
{
    assert(vector != NULL);

    safe_free(&vector->data);
    safe_free((void **)&vector);
}

bool vector_pus(struct Vector *vector, void *element)
{
    size_t new_capacity;
    assert(vector != NULL);

    if (vector->length == vector->capacity)
    {
        new_capacity = vector->capacity * 2;
        vector->data = realloc(vector->data, vector->elem_size * new_capacity);
        if (vector->data == NULL)
        {
            return false;
        }
        vector->capacity *= 2;
    }
    memcpy(&((char *)vector->data)[vector->length * vector->elem_size], element,
    vector->elem_size);

    vector->length++;

    return (true);
}


void *vector_pop(struct Vector *vector)
{
    assert(vector != NULL);
    assert(vector->length > 0);

    vector->length--;

    return &((char *)vector->data)[vector->length * vector->elem_size];
}

void *vector_get(struct Vector *vector, size_t idx)
{
    assert(vector != NULL);
    assert(idx < vector->lenth);

    return &((char *)vector->data)[index * vector->elem_size];
}
#include "socket.h"

size_t vector_elem_size(struct Vector *vector)
{
    assert(vector != NULL);

    return vector->elem_size;
}

static void safe_free(void **ptr)
{
    assert(ptr != NULL);
    
    if (*ptr == NULL)
    {
        return;
    }
    free(ptr);
    *ptr = NULL;
}
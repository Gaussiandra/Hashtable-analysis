#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vector.hpp"

#define RETURN_ON_ERROR(func) { int error = (func); if (error) return error; }

static inline void* get_ptr_by_vector_index(const struct vector *vector, size_t index) {
    assert(vector);
 
    return (char*) vector->array + (vector->elemSize * index);
}

struct vector *vector_new(size_t nElems, size_t elemSize) {
    assert(elemSize);

    struct vector *newVector = (struct vector*) calloc(1, sizeof(struct vector));

    newVector->size = newVector->capacity = nElems;
    newVector->elemSize = elemSize;
    newVector->array = calloc(newVector->capacity, newVector->elemSize);

    return newVector;
}

int vector_push(struct vector *vector, const void *element) {
    assert(vector);
    assert(element);

    if (vector->size == vector->capacity) {
        RETURN_ON_ERROR(change_vector_capacity(vector, vector->size * 2 + 1));
    }

    ++vector->size;
    RETURN_ON_ERROR(vector_set(vector, vector->size - 1, element));

    return 0;
}

int vector_pop(struct vector *vector, void *element) {
    assert(vector);
    assert(element);

    RETURN_ON_ERROR(vector_get(vector, vector->size - 1, element));
    --vector->size;

    return 0;
}

int vector_empty(struct vector const *vector) {
    assert(vector);

    return vector->size == 0;
}

struct vector *vector_delete(struct vector *vector) {
    assert(vector);

    free(vector->array);
    free(vector);

    return NULL;
}

void vector_print(struct vector const *vector, void (*print_func)(void const *vector)) {
    assert(vector);
    assert(print_func);

    printf("[");
    for (size_t idx = 0; vector->size && (idx < vector->size - 1); ++idx) {
        print_func(get_ptr_by_vector_index(vector, idx));
        printf(", ");
    }
    if (vector->size > 0) {
        print_func(get_ptr_by_vector_index(vector, vector->size - 1));
    }
    printf("]\n");
}

int vector_set(struct vector *vector, size_t index, void const *element) {
    assert(vector);
    assert(element);

    if (index >= vector->size) {
        return 1;
    }

    memcpy(get_ptr_by_vector_index(vector, index), element, vector->elemSize);
    return 0;
}

int vector_get(struct vector const *vector, size_t index, void *element) {
    assert(vector);
    assert(element);

    if (index >= vector->size) {
        return 1;
    }

    memcpy(element, get_ptr_by_vector_index(vector, index), vector->elemSize);
    return 0;
}

int change_vector_capacity(struct vector *vector, size_t newSize) {
    assert(vector);

    void *newPtr = realloc(vector->array, newSize * vector->elemSize); 
    if (!newPtr) {
        return 1;
    }
    
    vector->array = newPtr;
    vector->capacity = newSize;
    return 0;
}

int vector_resize(struct vector *vector, size_t newSize) {
    assert(vector);

    if (newSize > vector->capacity) {
        change_vector_capacity(vector, newSize);
    }
    vector->size = newSize;

    return 0;
}

size_t vector_size(struct vector const *vector) {
    assert(vector);

    return vector->size;
}
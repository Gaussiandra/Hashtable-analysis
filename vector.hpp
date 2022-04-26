#include <cstdlib>

struct vector {
    size_t size, capacity, elemSize;
    void *array;
};

// static inline void* get_ptr_by_vector_index(const struct vector *vector, size_t index);
struct vector *vector_new(size_t nElems, size_t elemSize);
int vector_push(struct vector *vector, void const *element);
int vector_pop (struct vector *vector, void *element);
int vector_empty(struct vector const *vector);
struct vector *vector_delete(struct vector *vector);
void vector_print(struct vector const *vector, void (*print_func)(void const *data));
int vector_set(struct vector *vector, size_t index, void const *element);
int vector_get(struct vector const *vector, size_t index, void *element);
int change_vector_capacity(struct vector *vector, size_t newSize);
int vector_resize(struct vector *vector, size_t new_size);
size_t vector_size(struct vector const *vector);
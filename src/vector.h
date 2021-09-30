#ifndef VECTOR_H
#define VECTOR_H

#include "stddef.h"
#include "shape.h"

struct shapes_vec {
    size_t length;
    size_t capacity;
    struct shape *start;
};

static const struct shapes_vec EMPTY_VEC;

struct shape* push(struct shapes_vec);
struct shape* pop(struct shapes_vec);
struct shape* get(struct shapes_vec, size_t index);

#endif
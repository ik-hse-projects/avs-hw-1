#ifndef VECTOR_H
#define VECTOR_H

#include "shape.h"
#include "stddef.h"

struct shapes_vec;

struct shapes_vec* empty_vec();
void free_vec(struct shapes_vec*);
struct shape* push(struct shapes_vec*);
struct shape* pop(struct shapes_vec*);
struct shape* get(struct shapes_vec*, size_t index);
size_t length(struct shapes_vec*);
void selection_sort_by_perimiter(struct shapes_vec*);

#endif
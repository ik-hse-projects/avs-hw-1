#include "vector.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

struct shapes_vec {
    size_t length;
    size_t capacity;
    struct shape* start;
};

struct shapes_vec* empty_vec() {
    return calloc(1, sizeof(struct shapes_vec));
}

void free_vec(struct shapes_vec* self) {
    free(self->start);
    free(self);
}

struct shape* push(struct shapes_vec* self) {
    size_t idx = self->length;
    if (idx >= self->capacity) {
        self->capacity = self->capacity * 2 + 1;
        void* new = calloc(sizeof(struct shape), self->capacity);

        if (self->start != NULL) {
            memcpy(new, self->start, self->length * sizeof(struct shape));
            free(self->start);
        }

        self->start = new;
    }
    self->length += 1;
    return get(self, idx);
}

struct shape* pop(struct shapes_vec* self) {
    self->length -= 1;
    size_t idx = self->length;
    return get(self, idx);
}

struct shape* get(struct shapes_vec* self, size_t index) {
    if (index >= self->length) {
        return NULL;
    }
    return self->start + index;
}

size_t length(struct shapes_vec* self) { return self->length; }

void selection_sort_by_perimiter(struct shapes_vec* shapes) {
    for (int i = 0; i < shapes->length; i++) {
        struct shape* smallest = shapes->start + i;
        int perimiter = perimiter_of_shape(*smallest);
        for (int j = i + 1; j < shapes->length; j++) {
            struct shape* other = shapes->start + j;
            int p = perimiter_of_shape(*other);
            if (p < perimiter) {
                smallest = other;
                perimiter = p;
            }
        }

        struct shape a = *smallest;
        struct shape b = shapes->start[i];
        shapes->start[i] = a;
        *smallest = b;
    }
}

void print_vector(struct shapes_vec* shapes) {
    for (size_t i = 0; i < shapes->length; ++i) {
        struct shape shape = *get(shapes, i);
        printf("%ld. ", i + 1);
        print_shape(shape);
        printf("\n");
    }
}

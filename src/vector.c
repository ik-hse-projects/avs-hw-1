#include "vector.h"
#include "stdlib.h"
#include "string.h"

struct shape* push(struct shapes_vec self) {
    size_t idx = self.length++;
    if (idx >= self.capacity) {
        void* new = malloc(self.capacity * 2);
        memcpy(new, self.start, self.length);
        self.capacity *= 2;
        self.start = new;
    }
    return get(self, idx);
}

struct shape* pop(struct shapes_vec self) {
    self.length -= 1;
    size_t idx = self.length;
    return get(self, idx);
}

struct shape* get(struct shapes_vec self, size_t index) {
    if (index >= self.length) {
        return NULL;
    }
    return self.start + index;
}

void selection_sort_by_perimiter(struct shapes_vec shapes) {
    for (int i = 0; i < shapes.length; i++) {
        struct shape *smallest = shapes.start + i;
        int perimiter = shape_perimiter(*smallest);
        for (int j = i+1; j < shapes.length; j++) {
            struct shape * other = shapes.start + j;
            int p = shape_perimiter(*other);
            if (p < perimiter) {
                smallest = other;
                perimiter = p;
            }
        }
        
        struct shape a = *smallest;
        struct shape b = shapes.start[i];
        shapes.start[i] = a;
        *smallest = b;
    }
}

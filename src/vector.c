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
    return self.start + index * sizeof(struct shape);
}
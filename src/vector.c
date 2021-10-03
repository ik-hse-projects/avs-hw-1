#include "vector.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct shapes_vec {
    size_t length;        // число инициализированных элементов
    size_t capacity;      // длина выделенной памяти, в элементах
    struct shape* start;  // указатель на начало текущего массива
};

// Создаёт пустой вектор
struct shapes_vec* empty_vec() {
    return calloc(1, sizeof(struct shapes_vec));
}

// Освобождает используемую вектором память
void free_vec(struct shapes_vec* self) {
    if (self->start != NULL) {
        free(self->start);
    }
    free(self);
}

// Возвращает указатель на только что добавленный элемент
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
    return self->start + idx;
}

// Возвращает указатель на только что удалённый элемент
struct shape* pop(struct shapes_vec* self) {
    self->length -= 1;
    size_t idx = self->length;
    return self->start + idx;
}

// Возвращает указатель требуемый что удалённый элемент.
// Может вернуть NULL, если неверный индекс.
struct shape* get(struct shapes_vec* self, size_t index) {
    if (index >= self->length) {
        return NULL;
    }
    return self->start + index;
}

// Текущая длина вектора.
size_t length(struct shapes_vec* self) { return self->length; }

// Сортирует фигуры по их периметру.
void selection_sort_by_perimiter(struct shapes_vec* shapes) {
    for (int i = 0; i < shapes->length; i++) {
        struct shape* smallest = shapes->start + i;
        double perimiter = perimiter_of_shape(*smallest);
        for (int j = i + 1; j < shapes->length; j++) {
            struct shape* other = shapes->start + j;
            double p = perimiter_of_shape(*other);
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

// Выводит содержимое вектора в указанный файл.
void print_vector(int fd, struct shapes_vec* shapes) {
    for (size_t i = 0; i < shapes->length; ++i) {
        struct shape shape = *get(shapes, i);
        dprintf(fd, "%ld. ", i + 1);
        print_shape(fd, shape);
        dprintf(fd, "\n");
    }
}

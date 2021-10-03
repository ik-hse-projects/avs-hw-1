#include "shape.h"

#include <stdio.h>

// Считывает параметры фигуры из буфера.
struct shape read_shape(struct buffer *buffer) {
    unsigned int kind = read_uint(buffer, 1, MAX_SHAPE);
    skip_whitespaces(buffer);
    switch (kind) {
        case CIRCLE: {
            struct circle circle = read_circle(buffer);
            struct shape result = {.kind = kind, .value = {.circle = circle}};
            return result;
        }
        case RECTANGLE: {
            struct rectangle rectangle = read_rectangle(buffer);
            struct shape result = {.kind = kind, .value = {.rectangle = rectangle}};
            return result;
        }
        case TRIANGLE: {
            struct triangle triangle = read_triangle(buffer);
            struct shape result = {.kind = kind, .value = {.triangle = triangle}};
            return result;
        }
    }
}

// Выводит информацию о фигуре в указанный файл.
void print_shape(int fd, struct shape shape) {
    switch (shape.kind) {
        case CIRCLE:
            dprintf(fd, "Circle: ");
            print_circle(fd, shape.value.circle);
            return;
        case RECTANGLE:
            dprintf(fd, "Rectangle: ");
            print_rectangle(fd, shape.value.rectangle);
            return;
        case TRIANGLE:
            dprintf(fd, "Triangle: ");
            print_triangle(fd, shape.value.triangle);
            return;
        default:
            dprintf(fd, "Unknown shape: %d", shape.kind);
            return;
    }
}

// Возвращает периметр фигуры.
double perimiter_of_shape(struct shape shape) {
    switch (shape.kind) {
        case CIRCLE:
            return perimiter_of_circle(shape.value.circle);
        case RECTANGLE:
            return perimiter_of_rectangle(shape.value.rectangle);
        case TRIANGLE:
            return perimiter_of_triangle(shape.value.triangle);
    }
}

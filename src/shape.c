#include "shape.h"

#include <stdio.h>

struct shape read_shape(struct buffer *buffer) {
    unsigned int kind = buf_uint(buffer, 1, MAX_SHAPE);
    buf_whitespace(buffer);
    switch (kind) {
        case CIRCLE: {
            struct circle circle = read_circle(buffer);
            struct shape result = {.kind = kind, .value = {.circle = circle}};
            return result;
        }
        case RECTANGLE: {
            struct rectangle rectangle = read_rectangle(buffer);
            struct shape result = {.kind = kind,
                                   .value = {.rectangle = rectangle}};
            return result;
        }
        case TRIANGLE: {
            struct triangle triangle = read_triangle(buffer);
            struct shape result = {.kind = kind,
                                   .value = {.triangle = triangle}};
            return result;
        }
    }
}

void print_shape(struct shape shape) {
    switch (shape.kind) {
        case CIRCLE:
            printf("Circle: ");
            print_circle(shape.value.circle);
            return;
        case RECTANGLE:
            printf("Rectangle: ");
            print_rectangle(shape.value.rectangle);
            return;
        case TRIANGLE:
            printf("Triangle: ");
            print_triangle(shape.value.triangle);
            return;
        default:
            printf("Unknown shape: %d", shape.kind);
            return;
    }
}

int perimiter_of_shape(struct shape shape) {
    switch (shape.kind) {
        case CIRCLE:
            return perimiter_of_circle(shape.value.circle);
        case RECTANGLE:
            return perimiter_of_rectangle(shape.value.rectangle);
        case TRIANGLE:
            return perimiter_of_triangle(shape.value.triangle);
    }
}

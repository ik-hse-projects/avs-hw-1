#include "shape.h"
#include <stdio.h>

struct shape shape_read(struct buffer *buffer) {
    unsigned int kind = buf_uint(buffer);
    buf_whitespace(buffer);
    switch (kind) {
        case CIRCLE:
        {
            struct circle circle = circle_read(buffer);
            struct shape result = {
                .kind = kind,
                .value = {
                    .circle = circle
                }
            };
            return result;
        }
        case RECTANGLE:
        {
            struct rectangle rectangle = rectangle_read(buffer);
            struct shape result = {
                .kind = kind,
                .value = {
                    .rectangle = rectangle
                }
            };
            return result;
        }
        case TRIANGLE:
        {
            struct triangle triangle = triangle_read(buffer);
            struct shape result = {
                .kind = kind,
                .value = {
                    .triangle = triangle
                }
            };
            return result;
        }
    }
}

void shape_print(struct shape shape) {
    switch (shape.kind) {
        case CIRCLE:
            printf("Circle: ");
            circle_print(shape.value.circle);
            return;
        case RECTANGLE:
            printf("Rectangle: ");
            rectangle_print(shape.value.rectangle);
            return;
        case TRIANGLE:
            printf("Triangle: ");
            triangle_print(shape.value.triangle);
            return;
        default:
            printf("Unknown shape: %d", shape.kind);
            return;
    }
}

int shape_perimiter(struct shape shape) {
    switch (shape.kind) {
        case CIRCLE:
            return circle_perimiter(shape.value.circle);
        case RECTANGLE:
            return rectangle_perimiter(shape.value.rectangle);
        case TRIANGLE:
            return triangle_perimiter(shape.value.triangle);
    }
}

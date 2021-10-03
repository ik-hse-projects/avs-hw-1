#ifndef SHAPE_H
#define SHAPE_H

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

struct shape {
    enum {
        CIRCLE = 1,
        RECTANGLE = 2,
        TRIANGLE = 3,
        MAX_SHAPE,
    } kind;
    union {
        struct circle circle;
        struct rectangle rectangle;
        struct triangle triangle;
    } value;
};

struct shape read_shape(struct buffer*);
void print_shape(int fd, struct shape);
double perimiter_of_shape(struct shape);

#endif
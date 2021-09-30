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
    } kind;
    union
    {
        struct circle circle;
        struct rectangle rectangle;
        struct triangle triangle;
    } value;
};

struct shape shape_read(struct buffer *buffer);
void shape_print(struct shape);
int shape_perimiter(struct shape);

#endif
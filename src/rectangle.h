#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "buffer.h"

struct rectangle
{
    struct point top_left;
    struct point bottom_right;
};

struct rectangle rectangle_read(struct buffer *buffer);
void rectangle_print(struct rectangle);
int rectangle_perimiter(struct rectangle);

#endif
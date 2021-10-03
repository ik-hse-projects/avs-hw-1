#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "buffer.h"
#include "color.h"
#include "point.h"

struct rectangle
{
    enum color color;
    struct point top_left;
    struct point bottom_right;
};

struct rectangle rectangle_read(struct buffer *buffer);
void rectangle_print(struct rectangle);
int rectangle_perimiter(struct rectangle);

#endif
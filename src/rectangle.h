#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "buffer.h"
#include "color.h"
#include "point.h"

struct rectangle {
    enum color color;
    struct point top_left;
    struct point bottom_right;
};

struct rectangle read_rectangle(struct buffer*);
void print_rectangle(struct rectangle);
int perimiter_of_rectangle(struct rectangle);

#endif
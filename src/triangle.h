#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "color.h"
#include "point.h"

struct triangle {
    enum color color;
    struct point a;
    struct point b;
    struct point c;
};

struct triangle read_triangle(struct buffer*);
void print_triangle(int fd, struct triangle);
int perimiter_of_triangle(struct triangle);

#endif
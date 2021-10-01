#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

struct triangle
{
    struct point a;
    struct point b;
    struct point c;
};

struct triangle triangle_read(struct buffer *buffer);
void triangle_print(struct triangle);
int triangle_perimiter(struct triangle);

#endif
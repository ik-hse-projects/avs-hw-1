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

struct triangle triangle_read(struct buffer*);
void triangle_print(struct triangle);
int triangle_perimiter(struct triangle);

#endif
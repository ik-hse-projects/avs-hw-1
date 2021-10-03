#ifndef CIRCLE_H
#define CIRCLE_H

#include "buffer.h"
#include "color.h"
#include "point.h"

struct circle {
    enum color color;
    struct point center;
    int radius;
};

struct circle circle_read(struct buffer*);
void circle_print(struct circle);
int circle_perimiter(struct circle);

#endif
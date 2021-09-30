#ifndef CIRCLE_H
#define CIRCLE_H

#include "buffer.h"
#include "point.h"

struct circle {
    struct point center;
    int radius;
};

struct circle circle_read(struct buffer *buffer);
void circle_print(struct circle);
int circle_perimiter(struct circle);

#endif
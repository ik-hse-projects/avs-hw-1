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

struct circle read_circle(struct buffer*);
void print_circle(int fd, struct circle);
double perimiter_of_circle(struct circle);

#endif
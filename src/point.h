#ifndef POINT_H
#define POINT_H

#include "buffer.h"

struct point {
    int x;
    int y;
};

double distance_between(struct point a, struct point b);
struct point read_point(struct buffer *buf);
void print_point(int fd, struct point self);

#endif
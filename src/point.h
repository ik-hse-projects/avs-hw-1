#ifndef POINT_H
#define POINT_H

#include "buffer.h"

struct point {
    int x;
    int y;
};

double distance_between(struct point a, struct point b);
struct point point_read(struct buffer *buf);
void point_print(struct point self);

#endif
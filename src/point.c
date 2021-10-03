#include "point.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>

double distance_between(struct point a, struct point b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt((double)(dx * dx + dy * dy));
}

struct point read_point(struct buffer *buf) {
    int x = buf_int(buf, 0, INT_MAX);
    buf_whitespace(buf);
    int y = buf_int(buf, 0, INT_MAX);

    struct point result = {
        .x = x,
        .y = y,
    };
    return result;
}

void print_point(struct point self) { printf("(%i, %i)", self.x, self.y); }
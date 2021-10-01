#include "point.h"
#include <math.h>

double distance_between(struct point a, struct point b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt(dx*dx + dy*dy);
}

struct point point_read(struct buffer *buf) {
    int x = buf_int(buf);
    buf_whitespace(buf);
    int y = buf_int(buf);

    struct point result = {
        .x = x,
        .y = y,
    };
    return result;
}

void point_print(struct point self) {
    printf("(%n, %n)", self.x, self.y);
}
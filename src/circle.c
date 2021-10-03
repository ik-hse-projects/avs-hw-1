#include "circle.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>

struct circle read_circle(struct buffer *buffer) {
    enum color color = read_color(buffer);
    buf_whitespace(buffer);
    struct point center = read_point(buffer);
    buf_whitespace(buffer);
    unsigned int radius = buf_uint(buffer, 0, UINT_MAX);

    struct circle result = {.color = color, .center = center, .radius = radius};
    return result;
}

void print_circle(struct circle self) {
    printf("color=");
    print_color(self.color);
    printf(", center=");
    print_point(self.center);
    printf(", radius=%u", self.radius);
}

int perimiter_of_circle(struct circle self) { return 2 * M_PI * self.radius; }
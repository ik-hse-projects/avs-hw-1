#include "circle.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>

struct circle circle_read(struct buffer *buffer) {
    enum color color = read_color(buffer);
    buf_whitespace(buffer);
    struct point center = point_read(buffer);
    buf_whitespace(buffer);
    unsigned int radius = buf_uint(buffer, 0, UINT_MAX);

    struct circle result = {.color = color, .center = center, .radius = radius};
    return result;
}

void circle_print(struct circle self) {
    printf("color: ");
    print_color(self.color);
    printf("; center: ");
    point_print(self.center);
    printf("; radius: %u", self.radius);
}

int circle_perimiter(struct circle self) { return 2 * M_PI * self.radius; }
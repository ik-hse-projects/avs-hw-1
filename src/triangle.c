#include "triangle.h"

#include <stdio.h>

struct triangle triangle_read(struct buffer *buffer) {
    enum color color = read_color(buffer);
    buf_whitespace(buffer);
    struct point a = point_read(buffer);
    buf_whitespace(buffer);
    struct point b = point_read(buffer);
    buf_whitespace(buffer);
    struct point c = point_read(buffer);

    struct triangle result = {
        .a = a,
        .b = b,
        .c = c,
    };
    return result;
}

void triangle_print(struct triangle self) {
    printf("color: ");
    print_color(self.color);
    printf("; points: ");
    point_print(self.a);
    printf(" - ");
    point_print(self.b);
    printf(" - ");
    point_print(self.c);
}

int triangle_perimiter(struct triangle self) {
    return distance_between(self.a, self.b) + distance_between(self.b, self.c) +
           distance_between(self.c, self.a);
}
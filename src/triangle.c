#include "triangle.h"

#include <stdio.h>

struct triangle read_triangle(struct buffer *buffer) {
    enum color color = read_color(buffer);
    buf_whitespace(buffer);
    struct point a = read_point(buffer);
    buf_whitespace(buffer);
    struct point b = read_point(buffer);
    buf_whitespace(buffer);
    struct point c = read_point(buffer);

    struct triangle result = {
        .a = a,
        .b = b,
        .c = c,
    };
    return result;
}

void print_triangle(struct triangle self) {
    printf("color=");
    print_color(self.color);
    printf(", points=");
    print_point(self.a);
    printf(" - ");
    print_point(self.b);
    printf(" - ");
    print_point(self.c);
}

int perimiter_of_triangle(struct triangle self) {
    return distance_between(self.a, self.b) + distance_between(self.b, self.c) +
           distance_between(self.c, self.a);
}
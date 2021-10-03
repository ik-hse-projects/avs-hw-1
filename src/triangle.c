#include "triangle.h"

#include <stdio.h>

// Считывает параметры треугольника из буфера.
struct triangle read_triangle(struct buffer *buffer) {
    enum color color = read_color(buffer);
    skip_whitespaces(buffer);
    struct point a = read_point(buffer);
    skip_whitespaces(buffer);
    struct point b = read_point(buffer);
    skip_whitespaces(buffer);
    struct point c = read_point(buffer);

    struct triangle result = {
        .a = a,
        .b = b,
        .c = c,
    };
    return result;
}

// Выводит информацию о треугольнике в указанный файл.
void print_triangle(int fd, struct triangle self) {
    dprintf(fd, "color=");
    print_color(fd, self.color);
    dprintf(fd, ", points=");
    print_point(fd, self.a);
    dprintf(fd, " - ");
    print_point(fd, self.b);
    dprintf(fd, " - ");
    print_point(fd, self.c);
}

// Возвращает периметр треугольника.
int perimiter_of_triangle(struct triangle self) {
    return distance_between(self.a, self.b) + distance_between(self.b, self.c) +
           distance_between(self.c, self.a);
}
#include "point.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>

// Возвращает расстояние между точками.
double distance_between(struct point a, struct point b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt((double)(dx * dx + dy * dy));
}

// Считывает параметры точки из буфера.
struct point read_point(struct buffer *buf) {
    int x = read_int(buf, 0, INT_MAX);
    skip_whitespaces(buf);
    int y = read_int(buf, 0, INT_MAX);

    struct point result = {
        .x = x,
        .y = y,
    };
    return result;
}

// Выводит информацию о точке в указанный файл.
void print_point(int fd, struct point self) { dprintf(fd, "(%i, %i)", self.x, self.y); }
#include "circle.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>

// Считывает параметры круга из буфера.
struct circle read_circle(struct buffer *buffer) {
    enum color color = read_color(buffer);
    skip_whitespaces(buffer);
    struct point center = read_point(buffer);
    skip_whitespaces(buffer);
    unsigned int radius = read_uint(buffer, 0, UINT_MAX);

    struct circle result = {.color = color, .center = center, .radius = radius};
    return result;
}

// Выводит информацию о круге в указанный файл.
void print_circle(int fd, struct circle self) {
    dprintf(fd, "color=");
    print_color(fd, self.color);
    dprintf(fd, ", center=");
    print_point(fd, self.center);
    dprintf(fd, ", radius=%u", self.radius);
}

// Возвращает периметр круга.
double perimiter_of_circle(struct circle self) { return M_PI * 2 * self.radius; }
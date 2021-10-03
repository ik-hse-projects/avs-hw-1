#ifndef COLOR_H
#define COLOR_H

#include "buffer.h"

enum color {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    LIGHT_BLUE,
    BLUE,
    PURPLE,
    MAX_COLOR,
};

enum color read_color(struct buffer *buf);
void print_color(enum color color);

#endif
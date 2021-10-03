#include "color.h"

#include <stdio.h>

enum color read_color(struct buffer *buf) {
    unsigned int color = buf_uint(buf, 1, MAX_COLOR);
    return color;
}

void print_color(int fd, enum color color) {
    switch (color) {
        case RED:
            dprintf(fd, "red");
            break;
        case ORANGE:
            dprintf(fd, "orange");
            break;
        case YELLOW:
            dprintf(fd, "yellow");
            break;
        case GREEN:
            dprintf(fd, "green");
            break;
        case LIGHT_BLUE:
            dprintf(fd, "light blue");
            break;
        case BLUE:
            dprintf(fd, "blue");
            break;
        case PURPLE:
            dprintf(fd, "purple");
            break;
        default:
            dprintf(fd, "unknown color");
            break;
    }
}
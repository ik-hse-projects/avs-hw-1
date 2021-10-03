#include "color.h"

#include <stdio.h>

enum color read_color(struct buffer *buf) {
    unsigned int color = buf_uint(buf, 1, MAX_COLOR);
    return color;
}

void print_color(enum color color) {
    switch (color) {
        case RED:
            printf("red");
            break;
        case ORANGE:
            printf("orange");
            break;
        case YELLOW:
            printf("yellow");
            break;
        case GREEN:
            printf("green");
            break;
        case LIGHT_BLUE:
            printf("light blue");
            break;
        case BLUE:
            printf("blue");
            break;
        case PURPLE:
            printf("purple");
            break;
        default:
            printf("unknown color");
            break;
    }
}
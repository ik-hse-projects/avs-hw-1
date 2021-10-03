#include "rectangle.h"

#include <stdio.h>

struct rectangle read_rectangle(struct buffer *buffer) {
    enum color color = read_color(buffer);
    buf_whitespace(buffer);
    struct point top_left = read_point(buffer);
    buf_whitespace(buffer);
    struct point bottom_right = read_point(buffer);

    struct rectangle result = {
        .color = color,
        .top_left = top_left,
        .bottom_right = bottom_right,
    };
    return result;
}

void print_rectangle(int fd, struct rectangle self) {
    dprintf(fd, "color=");
    print_color(fd, self.color);
    dprintf(fd, ", top-left=");
    print_point(fd, self.top_left);
    dprintf(fd, ", bottom-right=");
    print_point(fd, self.bottom_right);
}

int perimiter_of_rectangle(struct rectangle self) {
    int height = self.bottom_right.y - self.top_left.y;
    int width = self.bottom_right.x - self.top_left.x;
    return (height + width) * 2;
}

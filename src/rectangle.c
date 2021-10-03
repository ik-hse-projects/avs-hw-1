#include "rectangle.h"

#include <stdio.h>

struct rectangle rectangle_read(struct buffer *buffer) {
    enum color color = read_color(buffer);
    buf_whitespace(buffer);
    struct point top_left = point_read(buffer);
    buf_whitespace(buffer);
    struct point bottom_right = point_read(buffer);

    struct rectangle result = {
        .color = color,
        .top_left = top_left,
        .bottom_right = bottom_right,
    };
    return result;
}

void rectangle_print(struct rectangle self) {
    printf("color: ");
    print_color(self.color);
    printf("; top-left: ");
    point_print(self.top_left);
    printf("; bottom-right: ");
    point_print(self.bottom_right);
}

int rectangle_perimiter(struct rectangle self) {
    int height = self.bottom_right.y - self.top_left.y;
    int width = self.bottom_right.x - self.top_left.x;
    return (height + width) * 2;
}

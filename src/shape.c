#include "shape.h"

struct shape shape_read(struct buffer *buffer) {
    unsigned int kind = buf_uint(buffer);
    buf_whitespace(buffer);
    switch (kind) {
        case CIRCLE:
            struct circle circle = circle_read(buffer);
            struct shape result = {
                .kind = kind,
                .value = {
                    .circle = circle
                }
            };
            return result;
        case RECTANGLE:
            struct rectangle rectangle = rectangle_read(buffer);
            struct shape result = {
                .kind = kind,
                .value = {
                    .rectangle = rectangle
                }
            };
            return result;
        case TRIANGLE:
            struct triangle triangle = triangle_read(buffer);
            struct shape result = {
                .kind = kind,
                .value = {
                    .triangle = triangle
                }
            };
            return result;
    }
}

void shape_print(struct shape) {
}

int shape_perimiter(struct shape) {

}

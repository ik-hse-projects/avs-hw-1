#include "circle.h"
#include <math.h>

struct circle circle_read(struct buffer *buffer) {
    struct point center = point_read(buffer);
    unsigned int radius = buf_uint(buffer);
    
    struct circle result = {
        .center = center,
        .radius = radius
    };
    return result;
}

void circle_print(struct circle self) {
    printf("center: ");
    point_print(self.center);
    printf(", radius: %u", self.radius);
}

int circle_perimiter(struct circle self) {
    return 2 * M_PI * self.radius;
}
#include "point.h"
#include <math.h>

double distance(struct point a, struct point b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return sqrt(dx*dx + dy*dy);
}
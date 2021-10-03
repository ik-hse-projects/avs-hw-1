#include "shape.h"
#include <stdio.h>

int main(int argc, char** argv) {
    printf("\nEnter:\n");
    struct buffer * buffer = fd_to_buffer(0);
    printf("\nResult:\n");
    struct shape shape = shape_read(buffer);
    shape_print(shape);
    printf("\nDone:\n");
    free_buffer(buffer);
}
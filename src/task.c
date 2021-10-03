#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "shape.h"
#include "vector.h"

struct buffer* parse_args(int argc, char** argv) {
    if (argc <= 1) {
        printf("Finish input with EOF (Ctrl+D). Run with -h for help\n");
        return fd_to_buffer(0);
    }

    // Then we are expecting a option and argument.
    if (argc != 3) {
        return NULL;
    }
    char* option = argv[1];
    char* argument = argv[2];
    struct buffer* buffer;

    // Ensure that option looks like '-', symbol, '\0'
    if (!(option[0] == '-' && option[1] != '\0' && option[2] == '\0')) {
        return NULL;
    }
    switch (option[1]) {
        case 'f': {
            // Read from file
            int file = open(argument, 0);
            if (file < 0) {
                dprintf(2, "Can't open the file `%s`: %d", argument, errno);
                exit(1);
            }
            buffer = fd_to_buffer(file);
            break;
        }
        case 'r': {
            // Randomized
            int seed = atoi(argument);
            srand(seed);
            buffer = rand_buffer();
            break;
        }
    }
    return buffer;
}

int main(int argc, char** argv) {
    struct buffer* buffer = parse_args(argc, argv);
    if (buffer == NULL) {
        printf("Usage:\n");
        printf("  No args to read from stdin.\n");
        printf("  -f <filename> to read from file\n");
        printf("  -r <seed> to use random values\n");
        printf("Input format:\n");
        printf("  First line contains number of shapes.\n");
        printf("  In the following lines shapes are entered.\n");
        printf("  All values are separated using whitespace\n");
        printf("Shapes:\n");
        printf("  Circle:    `1 <color> <x> <y> <radius>`\n");
        printf("  Rectangle: `2 <color> <x1> <y1> <x2> <y2>`\n");
        printf("             where (x1, y1) is the left-upper corner\n");
        printf("             and (x2, y2) is the bottom-left.\n");
        printf("  Triangle:  `3 <color> <x1> <y1> <x2> <y2> <x3> <y3>`\n");
        printf("Colors:\n");
        for (enum color i = 1; i < MAX_COLOR; ++i) {
            printf("  %d. ", i);
            print_color(i);
            printf("\n");
        }
        return 1;
    }

    unsigned int count = buf_uint(buffer, 1, 30);
    struct shapes_vec* container = empty_vec();
    for (int i = 0; i < count; ++i) {
        buf_whitespace(buffer);
        struct shape shape = shape_read(buffer);
        *push(container) = shape;
    }
    selection_sort_by_perimiter(container);
    for (size_t i = 0; i < length(container); ++i) {
        struct shape shape = *get(container, i);
        printf("%ld. ", i + 1);
        shape_print(shape);
        printf("\n");
    }
    free_buffer(buffer);
    free_vec(container);
}

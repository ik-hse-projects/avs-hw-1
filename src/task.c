#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "shape.h"
#include "vector.h"

struct options {
    struct buffer* input;
    int output;
};

struct options parse_args(int argc, char** argv) {
    struct options result = {
        .input = NULL,
        .output = 1,
    };

    if (argc <= 1) {
        dprintf(1, "Finish input with EOF (Ctrl+D). Run with -h for help\n");
        result.input = fd_to_buffer(0);
        return result;
    }

    ++argv;
    while (*argv != 0) {
        char* option = *argv;
        // Ensure that option looks like '-', symbol, '\0'
        if (!(option[0] == '-' && option[1] != '\0' && option[2] == '\0')) {
            dprintf(2, "Invalid option: %s", option);
            exit(1);
        }
        ++argv;

        if (option[1] == 'h') {
            dprintf(1, "Usage:\n");
            dprintf(1, "  default: read from stdin, write to stdout.\n");
            dprintf(1, "  -r <seed> to use random values\n");
            dprintf(1, "  -f <filename> to read from file\n");
            dprintf(1, "  -o <filename> to set output file\n");
            dprintf(1, "Input format:\n");
            dprintf(1, "  First line contains number of shapes.\n");
            dprintf(1, "  In the following lines shapes are entered.\n");
            dprintf(1, "  All values are separated using whitespace\n");
            dprintf(1, "Shapes:\n");
            dprintf(1, "  Circle:    `1 <color> <x> <y> <radius>`\n");
            dprintf(1, "  Rectangle: `2 <color> <x1> <y1> <x2> <y2>`\n");
            dprintf(1,
                    "             where (x1, y1) is the left-upper corner\n");
            dprintf(1, "             and (x2, y2) is the bottom-left.\n");
            dprintf(1,
                    "  Triangle:  `3 <color> <x1> <y1> <x2> <y2> <x3> <y3>`\n");
            dprintf(1, "Colors:\n");
            for (enum color i = 1; i < MAX_COLOR; ++i) {
                dprintf(1, "  %d. ", i);
                print_color(1, i);
                dprintf(1, "\n");
            }
            exit(0);
        }

        char* argument = *argv;
        if (argv == NULL) {
            dprintf(2, "Expected argument after %s", option);
            exit(1);
        }
        ++argv;

        switch (option[1]) {
            case 'r': {
                // Randomized
                int seed = atoi(argument);
                srand(seed);
                result.input = rand_buffer();
                break;
            }
            case 'f': {
                // Read from file
                int file = open(argument, O_RDONLY);
                if (file < 0) {
                    dprintf(2, "Can't open the file `%s`: %d", argument, errno);
                    exit(1);
                }

                result.input = fd_to_buffer(file);
                break;
            }
            case 'o': {
                // Output to file
                int file = open(argument, O_WRONLY | O_CREAT, 0644);
                if (file < 0) {
                    dprintf(2, "Can't open the file `%s`: %d", argument, errno);
                    exit(1);
                }

                result.output = file;
                break;
            }
            default: {
                dprintf(2, "Unknown option: %s", option);
                exit(1);
            }
        }
    }

    return result;
}

int main(int argc, char** argv) {
    struct options options = parse_args(argc, argv);

    unsigned int count = buf_uint(options.input, 1, 30);
    struct shapes_vec* container = empty_vec();
    for (int i = 0; i < count; ++i) {
        buf_whitespace(options.input);
        struct shape shape = read_shape(options.input);
        *push(container) = shape;
    }

    dprintf(options.output, "Data:\n");
    print_vector(options.output, container);

    dprintf(options.output, "Sorted:\n");
    selection_sort_by_perimiter(container);
    print_vector(options.output, container);

    free_buffer(options.input);
    free_vec(container);
}

#include <unistd.h>
#include <stdlib.h>
#include "shape.h"

struct buffer * parse_args(int argc, char** argv) {
    if (argc <= 1) {
        return fd_to_buffer(0);
    }

    // Then we are expecting a option and argument.
    if (argc != 3) {
        return NULL;
    }
    char* option = argv[1];
    char* argument = argv[2];
    struct buffer * buffer;

    // Ensure that option looks like '-', symbol, '\0'
    if (!(option[0] == '-' && option[1] != '\0' && option[2] == '\0')) {
        return NULL;
    }
    switch (option[1]) {
        case 'f':
        {
            // Read from file
            int file = open(argument, "r");
            buffer = fd_to_buffer(file);
            break;
        }
        case 'r':
        {
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
    struct buffer * buffer = parse_args(argc, argv);
    if (buffer == NULL) {
        printf("Usage:\n");
        printf("    No args to read from stdin\n");
        printf("    -f <filename> to read from file\n");
        printf("    -r <seed> to use random values\n");
        return 1;
    }

    printf("\nResult:\n");
    struct shape shape = shape_read(buffer);
    shape_print(shape);
    printf("\nDone:\n");
    free_buffer(buffer);
}

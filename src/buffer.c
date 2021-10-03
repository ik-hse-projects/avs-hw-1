#include "buffer.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct buffer {
    size_t position;
    char *start;
    struct buffer *next;
};

struct buffer *fd_to_buffer(int fd) {
    const size_t CHUNK_SIZE = 4096;
    struct buffer *result = calloc(1, sizeof(struct buffer));
    struct buffer *last = result;
    while (1) {
        char *buffer = malloc(CHUNK_SIZE);
        int length = read(fd, buffer, CHUNK_SIZE - 1);
        if (length == 0) {
            last->start = NULL;
            free(buffer);
            return result;
        }
        struct buffer *next = calloc(1, sizeof(struct buffer));
        last->start = buffer;
        last->next = next;
        last = next;
    }
}

struct buffer *rand_buffer() {
    struct buffer *result = calloc(1, sizeof(struct buffer));
    result->position = SIZE_MAX;
    return result;
}

char read_current(struct buffer *self) {
    if (self->start == NULL || self->position == SIZE_MAX) {
        return 0;
    }
    char ch = self->start[self->position];
    if (ch != 0) {
        return ch;
    }
    if (self->next == 0) {
        return 0;
    }
    struct buffer next = *(self->next);
    free(self->start);
    free(self->next);
    *self = next;
    return read_current(self);
}

unsigned int random_in_range(unsigned int lower, unsigned int upper) {
    unsigned int range = upper - lower;
    unsigned int num = rand();
    unsigned int result = (num % range) + lower;
    return result;
}

unsigned int buf_uint(struct buffer *self, unsigned int lower,
                      unsigned int upper) {
    if (self->position == SIZE_MAX) {
        return random_in_range(lower, upper);
    }

    unsigned int result = 0;
    char is_any = 0;
    while (1) {
        char c = read_current(self);
        if ('0' <= c && c <= '9') {
            result = (10 * result) + (c - '0');
            self->position++;
            is_any = 1;
        } else {
            break;
        }
    }
    if (!is_any) {
        dprintf(2, "Expected number @ %d\n", self->position);
        exit(1);
    }
    return result;
}

int buf_int(struct buffer *self, unsigned int lower, unsigned int upper) {
    if (self->position == SIZE_MAX) {
        return random_in_range(lower, upper);
    }

    int sign = 1;
    if (read_current(self) == '-') {
        sign = -1;
        self->position++;
    }
    int result = buf_uint(self, 0, UINT_MAX);
    result *= sign;

    return result;
}

void buf_whitespace(struct buffer *self) {
    if (self->position == SIZE_MAX) {
        return;
    }
    char is_any = 0;
    while (1) {
        char c = read_current(self);
        if (c == '\t' || c == ' ' || c == '\r' || c == '\n') {
            self->position++;
            is_any = 1;
        } else {
            break;
        }
    }
    if (!is_any) {
        dprintf(2, "Expected whitespace @ %d\n", self->position);
        exit(1);
    }
}

void free_buffer(struct buffer *self) {
    if (self->start != NULL) {
        free(self->start);
        self->start = NULL;
    }
    if (self->next != NULL) {
        free_buffer(self->next);
        self->next = NULL;
    }
    free(self);
}

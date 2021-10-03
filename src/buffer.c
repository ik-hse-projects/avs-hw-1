#include "buffer.h"
#include <stdlib.h>
#include <unistd.h>

struct buffer {
    size_t position;
    char* start;
    struct buffer *next;
};

struct buffer * fd_to_buffer(int fd ) {
    const size_t CHUNK_SIZE = 4096;
    struct buffer *result = calloc(1, sizeof(struct buffer));
    struct buffer *last = result;
    while (1) {
        char* buffer = malloc(CHUNK_SIZE);
        int length = read(fd, buffer, CHUNK_SIZE - 1);
        if (length == 0) {
            free(buffer);
            return result;
        }
        struct buffer * next = calloc(1, sizeof(struct buffer));
        last->start = buffer;
        last->next = next;
        last = next;
    }
}

char read_current(struct buffer *self) {
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

unsigned int buf_uint(struct buffer *self) {
    unsigned int result = 0;
    while (1) {
        char c = read_current(self);
        if ('0' <= c && c <= '9') {
            result = (10 * result) + (c - '0');
            self->position++;
        } else {
            break;
        }
    }
    return result;
}

int buf_int(struct buffer *self) {
    int sign = 1;
    if (read_current(self) == '-') {
        sign = -1;
        self->position++;
    }
    unsigned int result = buf_uint(self);
    return sign * result;
}

void buf_whitespace(struct buffer *self) {
    while (1) {
        char c = read_current(self);
        if (c == '\t' || c == ' ') {
            self->position++;
        } else {
            break;
        }
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

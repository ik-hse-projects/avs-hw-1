#include "buffer.h"

struct buffer {
    size_t position;
    char* start;
    struct buffer *next;
};

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

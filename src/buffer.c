#include "buffer.h"

unsigned int buf_uint(struct buffer *self) {
    unsigned int result = 0;
    while (1) {
        char c = self->start[self->position];
        if ('0' <= c && c <= '9') {
            result = (10 * result) + (c - '0');
            self->position++;
        } else {
            break;
        }
    }
    return result;
}

void buf_whitespace(struct buffer *self) {
    while (1) {
        char c = self->start[self->position];
        if (c == '\t' || c == ' ') {
            self->position++;
        } else {
            break;
        }
    }
}

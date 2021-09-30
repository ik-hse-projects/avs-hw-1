#ifndef BUFFER_H
#define BUFFER_H

#include "stddef.h"

struct buffer {
    size_t position;
    char* start;
};

unsigned int buf_uint(struct buffer *self);
void buf_whitespace(struct buffer *self);

#endif
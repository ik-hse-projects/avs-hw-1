#ifndef BUFFER_H
#define BUFFER_H

#include "stddef.h"

struct buffer;

unsigned int buf_uint(struct buffer *self);
int buf_int(struct buffer *self);
void buf_whitespace(struct buffer *self);

#endif
#ifndef BUFFER_H
#define BUFFER_H

#include "stddef.h"

struct buffer;

struct buffer * fd_to_buffer(int fd);
unsigned int buf_uint(struct buffer *self);
int buf_int(struct buffer *self);
void buf_whitespace(struct buffer *self);
void free_buffer(struct buffer *self);

#endif
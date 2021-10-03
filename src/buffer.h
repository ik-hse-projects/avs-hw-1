#ifndef BUFFER_H
#define BUFFER_H

#include "stddef.h"

struct buffer;

struct buffer *fd_to_buffer(int fd);
struct buffer *rand_buffer();
unsigned int read_uint(struct buffer *self, unsigned int lower, unsigned int upper);
int read_int(struct buffer *self, unsigned int lower, unsigned int upper);
void skip_whitespaces(struct buffer *self);
void free_buffer(struct buffer *self);

#endif
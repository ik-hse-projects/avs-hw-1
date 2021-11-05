#include "buffer.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Реализация хранения, разбора и генерации (при необходимости) входных данных.
 */

struct buffer {
    int fd;  // десриптор файла, из которого происходит чтение, либо -1
    int mirror;  // дескриптор файла, в который надо дублировать ввод
    size_t position;  // текущая позиция во всём файле
    size_t offset;    // позиция начала чанка
    char* start;  // указатель на содержимое текущего чанка
};

// Переносит данные из файлового дескриптора в память.
struct buffer* fd_to_buffer(int fd) {
    struct buffer* result = calloc(1, sizeof(struct buffer));
    result->fd = fd;
    return result;
}

// Создаёт buffer, содержащий случайные данные
struct buffer* rand_buffer() {
    return fd_to_buffer(-1);
}

// Настраивает дублирование ввода в файл
void set_mirror(struct buffer* self, int fd) {
    self->mirror = fd;
}

// Возвращает текущий символ буфера
char read_current(struct buffer* self) {
    if (self->fd == -1 || self->position == SIZE_MAX) {
        return 0;
    }
    if (self->start != NULL) {
        char ch = self->start[self->position - self->offset];
        if (ch != 0) {
            return ch;
        }
    }

    const size_t CHUNK_SIZE = 4096;
    if (self->start == NULL) {
        self->start = calloc(CHUNK_SIZE, sizeof(char));
    }
    ssize_t length = read(self->fd, self->start, CHUNK_SIZE - 1);
    if (length <= 0) {
        // Failed to read or EOF
        self->position = SIZE_MAX;
        return 0;
    } else {
        self->offset = self->position;
        self->start[length] = 0;
    }

    return self->start[0];
}

// Возвращает случайное число в указанном диапазоне
unsigned int random_in_range(unsigned int lower, unsigned int upper) {
    unsigned int range = upper - lower;
    unsigned int num = rand();
    unsigned int result = (num % range) + lower;
    return result;
}

static char BUFFER[20] = {0};

void write_mirror(struct buffer* self) {
    if (self->mirror != -1) {
        write(self->mirror, BUFFER, strlen(BUFFER));
    }
}

// Считывает из буфера беззнаковое целое. Возможно, случайное в указанном
// диапазоне.
unsigned int read_uint_internal(struct buffer* self,
                                unsigned int lower,
                                unsigned int upper) {
    if (self->fd == SIZE_MAX) {
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
        dprintf(2, "Expected number @ %ld, found '%d'\n", self->position,
                read_current(self));
        exit(1);
    }
    return result;
}

unsigned int read_uint(struct buffer* self,
                       unsigned int lower,
                       unsigned int upper) {
    unsigned int result = read_uint_internal(self, lower, upper);
    snprintf(BUFFER, sizeof(BUFFER), "%u", result);
    write_mirror(self);
    return result;
}

// Считывает из буфера знаковое целое. Возможно, случайное в указанном
// диапазоне.
int read_int_internal(struct buffer* self,
                      unsigned int lower,
                      unsigned int upper) {
    if (self->fd == SIZE_MAX) {
        return random_in_range(lower, upper);
    }

    int sign = 1;
    if (read_current(self) == '-') {
        sign = -1;
        self->position++;
    }
    int result = read_uint_internal(self, 0, UINT_MAX);
    result *= sign;

    return result;
}

int read_int(struct buffer* self, unsigned int lower, unsigned int upper) {
    int result = read_int_internal(self, lower, upper);
    snprintf(BUFFER, sizeof(BUFFER), "%i", result);
    write_mirror(self);
    return result;
}

// Пропускает пробельные символы в буфере.
void skip_whitespaces(struct buffer* self) {
    if (self->fd == SIZE_MAX) {
        return;
    }
    char is_any = 0;
    while (1) {
        char c = read_current(self);
        if (c == '\r' || c == '\n') {
            BUFFER[0] = '\n';
            BUFFER[1] = '\0';
            write_mirror(self);
        } else if (c == '\t' || c == ' ') {
        } else {
            break;
        }
        self->position++;
        is_any = 1;
    }
    if (!is_any) {
        dprintf(2, "Expected whitespace @ %ld, found '%c'\n", self->position,
                read_current(self));
        exit(1);
    }
    BUFFER[0] = ' ';
    BUFFER[1] = '\0';
    write_mirror(self);
}

// Освобождает память за буфером.
void free_buffer(struct buffer* self) {
    if (self->start != NULL) {
        free(self->start);
        self->start = NULL;
    }
    free(self);
}

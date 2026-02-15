#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>
#include <sys/types.h>

size_t ft_strlen(const char *string_pointer);
char *ft_strcpy(char *destination_pointer, const char *source_pointer);
int ft_strcmp(const char *left_string_pointer, const char *right_string_pointer);
ssize_t ft_write(int file_descriptor, const void *buffer_pointer, size_t byte_count);
ssize_t ft_read(int file_descriptor, void *buffer_pointer, size_t byte_count);
char *ft_strdup(const char *source_pointer);

#endif

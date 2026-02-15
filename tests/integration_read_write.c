#include "libasm.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    const char *input_path;
    const char *output_path;
    int input_fd;
    int output_fd;
    char buffer[1024];
    ssize_t bytes_read;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <input_path> <output_path>\n", argv[0]);
        return 1;
    }

    input_path = argv[1];
    output_path = argv[2];

    input_fd = open(input_path, O_RDONLY);
    if (input_fd < 0)
    {
        perror("open input");
        return 1;
    }

    output_fd = open(output_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (output_fd < 0)
    {
        perror("open output");
        close(input_fd);
        return 1;
    }

    while (1)
    {
        bytes_read = ft_read(input_fd, buffer, sizeof(buffer));
        if (bytes_read < 0)
        {
            perror("ft_read");
            close(input_fd);
            close(output_fd);
            return 1;
        }
        if (bytes_read == 0)
            break;

        if (ft_write(output_fd, buffer, (size_t)bytes_read) != bytes_read)
        {
            if (errno != 0)
                perror("ft_write");
            else
                fprintf(stderr, "ft_write: short write\n");
            close(input_fd);
            close(output_fd);
            return 1;
        }
    }

    close(input_fd);
    close(output_fd);
    return 0;
}

#include "libasm.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int g_failures = 0;

static void report_test(const char *test_name, int passed)
{
    if (passed)
        printf("[OK]   %s\n", test_name);
    else
    {
        printf("[FAIL] %s\n", test_name);
        g_failures++;
    }
}

int main(void)
{
    char destination_buffer[32];
    char read_buffer[8];
    char *duplicated;
    ssize_t io_result;
    int file_descriptor;

    report_test("ft_strlen empty", ft_strlen("") == 0);
    report_test("ft_strlen normal", ft_strlen("libasm") == 6);

    memset(destination_buffer, 0, sizeof(destination_buffer));
    report_test("ft_strcpy return", ft_strcpy(destination_buffer, "hello") == destination_buffer);
    report_test("ft_strcpy content", strcmp(destination_buffer, "hello") == 0);

    report_test("ft_strcmp equal", ft_strcmp("abc", "abc") == 0);
    report_test("ft_strcmp less", ft_strcmp("abc", "abd") < 0);
    report_test("ft_strcmp greater", ft_strcmp("abd", "abc") > 0);

    errno = 0;
    io_result = ft_write(1, "ft_write works\n", 15);
    report_test("ft_write success", io_result == 15);

    errno = 0;
    io_result = ft_write(-1, "x", 1);
    report_test("ft_write invalid fd return", io_result == -1);
    report_test("ft_write invalid fd errno", errno == EBADF);

    file_descriptor = open("/dev/null", O_RDONLY);
    io_result = ft_read(file_descriptor, read_buffer, sizeof(read_buffer));
    close(file_descriptor);
    report_test("ft_read /dev/null", io_result == 0);

    errno = 0;
    io_result = ft_read(-1, read_buffer, sizeof(read_buffer));
    report_test("ft_read invalid fd return", io_result == -1);
    report_test("ft_read invalid fd errno", errno == EBADF);

    duplicated = ft_strdup("duplicate me");
    report_test("ft_strdup alloc", duplicated != NULL);
    report_test("ft_strdup content", duplicated != NULL && strcmp(duplicated, "duplicate me") == 0);
    report_test("ft_strdup pointer", duplicated != NULL && duplicated != "duplicate me");
    free(duplicated);

    duplicated = ft_strdup("");
    report_test("ft_strdup empty", duplicated != NULL && strcmp(duplicated, "") == 0);
    free(duplicated);

    if (g_failures != 0)
    {
        printf("\n%d test(s) failed\n", g_failures);
        return 1;
    }

    printf("\nAll tests passed\n");
    return 0;
}

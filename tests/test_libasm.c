#include "libasm.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static int g_failures = 0;

static int sign_of_int(int value)
{
    if (value < 0)
        return -1;
    if (value > 0)
        return 1;
    return 0;
}

static void assert_true(const char *name, int condition)
{
    if (condition)
    {
        printf("[OK]   %s\n", name);
        return;
    }
    printf("[FAIL] %s\n", name);
    g_failures++;
}

static void fill_random_text(char *buffer, size_t length)
{
    static const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    size_t i;

    for (i = 0; i < length; i++)
        buffer[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    buffer[length] = '\0';
}

static void test_strlen_against_libc(void)
{
    char test_buffer[513];
    int i;

    assert_true("strlen empty", ft_strlen("") == strlen(""));
    assert_true("strlen simple", ft_strlen("hello") == strlen("hello"));

    for (i = 0; i < 200; i++)
    {
        size_t length = (size_t)(rand() % 512);
        fill_random_text(test_buffer, length);
        if (ft_strlen(test_buffer) != strlen(test_buffer))
        {
            assert_true("strlen randomized", 0);
            return;
        }
    }
    assert_true("strlen randomized", 1);
}

static void test_strcpy_against_libc(void)
{
    char source_buffer[257];
    char dst_ft[257];
    char dst_libc[257];
    int i;

    for (i = 0; i < 200; i++)
    {
        size_t length = (size_t)(rand() % 256);
        fill_random_text(source_buffer, length);
        memset(dst_ft, 0x55, sizeof(dst_ft));
        memset(dst_libc, 0x55, sizeof(dst_libc));

        if (ft_strcpy(dst_ft, source_buffer) != dst_ft)
        {
            assert_true("strcpy return pointer", 0);
            return;
        }
        strcpy(dst_libc, source_buffer);

        if (memcmp(dst_ft, dst_libc, sizeof(dst_ft)) != 0)
        {
            assert_true("strcpy content", 0);
            return;
        }
    }

    assert_true("strcpy return pointer", 1);
    assert_true("strcpy content", 1);
}

static void test_strcmp_against_libc(void)
{
    char left_buffer[257];
    char right_buffer[257];
    int i;

    assert_true("strcmp equal literal", ft_strcmp("abc", "abc") == 0);

    for (i = 0; i < 400; i++)
    {
        size_t left_length = (size_t)(rand() % 256);
        size_t right_length = (size_t)(rand() % 256);
        int ft_value;
        int libc_value;

        fill_random_text(left_buffer, left_length);
        fill_random_text(right_buffer, right_length);

        ft_value = ft_strcmp(left_buffer, right_buffer);
        libc_value = strcmp(left_buffer, right_buffer);

        if (sign_of_int(ft_value) != sign_of_int(libc_value))
        {
            assert_true("strcmp randomized sign", 0);
            return;
        }
    }

    assert_true("strcmp randomized sign", 1);
}

static void test_write_read_behavior(void)
{
    int pipe_fds[2];
    const char *message = "libasm pipe test";
    char read_buffer[64];
    ssize_t write_result;
    ssize_t read_result;

    if (pipe(pipe_fds) != 0)
    {
        assert_true("pipe setup", 0);
        return;
    }

    write_result = ft_write(pipe_fds[1], message, strlen(message));
    read_result = ft_read(pipe_fds[0], read_buffer, sizeof(read_buffer));

    close(pipe_fds[0]);
    close(pipe_fds[1]);

    assert_true("write pipe count", write_result == (ssize_t)strlen(message));
    assert_true("read pipe count", read_result == (ssize_t)strlen(message));
    assert_true("read pipe content", read_result >= 0 && memcmp(read_buffer, message, (size_t)read_result) == 0);

    errno = 0;
    write_result = ft_write(-1, "x", 1);
    assert_true("write bad fd return", write_result == -1);
    assert_true("write bad fd errno", errno == EBADF);

    errno = 0;
    read_result = ft_read(-1, read_buffer, sizeof(read_buffer));
    assert_true("read bad fd return", read_result == -1);
    assert_true("read bad fd errno", errno == EBADF);
}

static void test_strdup_against_libc(void)
{
    char source_buffer[257];
    char *dup;
    int i;

    dup = ft_strdup("");
    assert_true("strdup empty alloc", dup != NULL);
    assert_true("strdup empty content", dup != NULL && strcmp(dup, "") == 0);
    free(dup);

    for (i = 0; i < 200; i++)
    {
        size_t length = (size_t)(rand() % 256);
        fill_random_text(source_buffer, length);
        dup = ft_strdup(source_buffer);
        if (dup == NULL)
        {
            assert_true("strdup randomized alloc", 0);
            return;
        }
        if (strcmp(dup, source_buffer) != 0 || dup == source_buffer)
        {
            free(dup);
            assert_true("strdup randomized content/pointer", 0);
            return;
        }
        free(dup);
    }

    assert_true("strdup randomized alloc", 1);
    assert_true("strdup randomized content/pointer", 1);
}

int main(void)
{
    srand((unsigned int)time(NULL));

    test_strlen_against_libc();
    test_strcpy_against_libc();
    test_strcmp_against_libc();
    test_write_read_behavior();
    test_strdup_against_libc();

    if (g_failures != 0)
    {
        printf("\n%d check(s) failed\n", g_failures);
        return 1;
    }

    printf("\nAll checks passed\n");
    return 0;
}

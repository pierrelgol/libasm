NAME = libasm.a

NASM = nasm
NASMFLAGS = -f elf64 -g
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_ASM = \
	src/ft_strlen.s \
	src/ft_strcpy.s \
	src/ft_strcmp.s \
	src/ft_write.s \
	src/ft_read.s \
	src/ft_strdup.s
OBJ_ASM = $(SRC_ASM:.s=.o)

TEST_NAME = libasm_test
TEST_SRC = main.c
CHECK_NAME = libasm_check
CHECK_SRC = tests/test_libasm.c

all: $(NAME)

$(NAME): $(OBJ_ASM)
	ar rcs $(NAME) $(OBJ_ASM)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

$(TEST_NAME): $(TEST_SRC) $(NAME) include/libasm.h
	$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) -o $(TEST_NAME)

$(CHECK_NAME): $(CHECK_SRC) $(NAME) include/libasm.h
	$(CC) $(CFLAGS) $(CHECK_SRC) $(NAME) -o $(CHECK_NAME)

test: $(TEST_NAME)

run: test
	./$(TEST_NAME)

check: $(CHECK_NAME)
	./$(CHECK_NAME)

clean:
	rm -f $(OBJ_ASM)

fclean: clean
	rm -f $(NAME) $(TEST_NAME) $(CHECK_NAME)

re: fclean all

.PHONY: all clean fclean re test run check

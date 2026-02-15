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
	src/ft_read.s
OBJ_ASM = $(SRC_ASM:.s=.o)

TEST_NAME = libasm_test
TEST_SRC = main.c
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_ASM)
	ar rcs $(NAME) $(OBJ_ASM)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_ASM) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re

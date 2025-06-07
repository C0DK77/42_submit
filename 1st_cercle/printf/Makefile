
NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs

SRC = ft_printf.c ft_printf_utils.c
OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${AR} ${NAME} ${OBJ}

%.o: %.c 
	$(CC) $(CFAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
NAME = fractol

CC = gcc
CFLAGS = -Wall -marche=native
LIBFT = libft/
MLX = mlx/

all : libft ${NAME}

%.o: %.c
	${CC} -fopenmp ${OBJECTS} -L./libft -lft -fopenmp -L./mlx -lmlx_Linux -l
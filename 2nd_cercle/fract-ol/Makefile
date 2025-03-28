
# ==== PROGRAM NAME ==== #

NAME = FRACTOL_H

# ==== COMPILER AND FLAGS ==== #

CC = cc
CFLAGS = -Wall -marche=native

# ==== FILES ==== #

LIBFT_DIR = libft/
MLX = mlx/



all : libft ${NAME}

%.o: %.c
	${CC} -fopenmp ${OBJECTS} -L./libft -lft -fopenmp -L./mlx -lmlx_Linux -l

# ==== PROGRAM NAME ==== #

NAME = fractol

# ==== COMPILER AND FLAGS ==== #

CC = cc 
CFLAGS = 	-Wall -Wextra -Werror \
			-I$(PRINTF_DIR) \
			-I$(LIBFT_DIR) \
			-I$(MLX_DIR)/includes

# ==== FILES SRC ==== #

SRC = $(wildcard *.c)

SRC_DIR = ./
OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# ==== LIBFT / PRINTF ==== #

LIBFT_DIR = ../../1.libft
PRINTF_DIR = ../../1st_cercle/printf
MLX_DIR    = ./mlx
LIBFT_A = $(LIBFT_DIR)/libft.a
PRINTF_A = $(PRINTF_DIR)/ft_printf.a
MLX_LIBS  = -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd -lm

# ==== RULES ==== #

all : $(LIBFT_A) $(PRINTF_A) $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A) $(PRINTF_A) $(MLX_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "🔧 Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) :
	@make -s -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)

$(PRINTF_A) :
	@make -s -C $(PRINTF_DIR)

clean :
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(PRINTF_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean : clean 
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(PRINTF_DIR) fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
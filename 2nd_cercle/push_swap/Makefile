
# ==== PROGRAM NAME ==== #

NAME = push_swap

# ==== COMPILER AND FLAGS ==== #

CC = cc 
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

# ==== FILES ==== #

SRC =	push_swap.c \
		1_sorting_functions.c \
		2_creation_lists.c \
		3_verifications.c \
		4_rules.c

SRC_DIR = ./
OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# ==== LIBFT ==== #

LIBFT_DIR = ../../1.libft
LIBFT_A = $(LIBFT_DIR)/libft.a 

# ==== RULES ==== #

all : $(LIBFT_A) $(NAME)

$(NAME) : $(OBJ)
	@echo "🔧 Link du binaire '$(NAME)'..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_A)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "📦 Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) :
	@echo "📚 Compilation de la libft..."
	@make -s -C $(LIBFT_DIR)

clean :
	@echo "🧹 Suppression des fichiers objets..."
	@make -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean : clean 
	@echo "🧨 Suppression des exécutables..."
	@make -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
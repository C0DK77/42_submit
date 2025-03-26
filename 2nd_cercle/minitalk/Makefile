
# ==== PROGRAM NAME ==== #

NAME_SERVER = server
NAME_CLIENT = client

# ==== FLAGS AND COMPILER ==== #

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)
CC = cc

# ==== FILES ==== #

SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_DIR = obj
OBJ_SERVER = $(addprefix $(OBJ_DIR)/, $(SRC_SERVER:.c=.o))
OBJ_CLIENT = $(addprefix $(OBJ_DIR)/, $(SRC_CLIENT:.c=.o))

# ==== LIBFT ==== #

LIBFT_DIR = ../../1.libft
LIBFT_A = $(LIBFT_DIR)/libft.a

# ==== RULES ==== #

all : $(LIBFT_A) $(OBJ_DIR) $(NAME_SERVER) $(NAME_CLIENT)
	@echo "✅ Compilation terminée !"

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(LIBFT_A) :
	@echo "📚 Compilation de la libft..."
	@make -s -C $(LIBFT_DIR)

$(NAME_SERVER) : $(OBJ_SERVER) $(LIBFT_A)
	@echo "🔧 Link du binaire 'server'..."
	@$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT_A)

$(NAME_CLIENT) : $(OBJ_CLIENT) $(LIBFT_A)
	@echo "🔧 Link du binaire 'client'..."
	@$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT_A)

$(OBJ_DIR)/%.o: %.c
	@echo "📦 Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo "🧹 Suppression des fichiers objets..."
	@make -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "🧨 Suppression des exécutables..."
	@make -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME_SERVER) $(NAME_CLIENT)

re : fclean all

.PHONY : all clean fclean re

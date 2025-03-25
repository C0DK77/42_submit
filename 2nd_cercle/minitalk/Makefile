
# ==== PROGRAM NAME ==== #

NAME_SERVER = server
NAME_CLIENT = client

# ==== FLAGS AND COMPILER ==== #

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)
CC = CC

# ==== FILES ==== #

SRC_SERVER = server.c utils.c 
SRC_CLIENT = client.c utils.c 

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# ==== LIBFT ==== #

LIBFT_DIR = ../libft
LIBFT_A = $(LIBFT_DIR)/libft.a

# ==== RULES ==== #

all : $(LIBFT_A) $(NAME_SERVER) $(NAME_CLIENT)
	@echo "✅ Compilation terminée !"

$(LIBFT_A) :
	@echo "📚 Compilation de la libft..."
	@make -C $(LIBFT_A)

$(NAME_SERVER) : $(OBJ_SERVER)
	@echo "🔧 Link du binaire 'server'..."
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT_A)

$(NAME_CLIENT) : $(OBJ_CLIENT)
	@echo "🔧 Link du binaire 'client'..."
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT_A)

%.o: %.c
	@echo "📦 Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo "🧹 Suppression des fichiers objets..."
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	make -C $(LIBFT_DIR) clean

fclean : clean
	@echo "🧨 Suppression des exécutables..."
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(LIBFT_DIR) clean

re : fclean all

.PHONY : all clean fclean re

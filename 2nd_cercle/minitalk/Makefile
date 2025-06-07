
# ==== PROGRAM NAME ==== #

NAME_SERVER = server
NAME_CLIENT = client

NAME_BONUS_SERVER = server_bonus
NAME_BONUS_CLIENT = client_bonus

# ==== FLAGS AND COMPILER ==== #

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR)
CC = cc

# ==== FILES ==== #

SRC_SERVER = server.c
SRC_CLIENT = client.c

SRC_BONUS_SERVER = server_bonus.c
SRC_BONUS_CLIENT = client_bonus.c

OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

OBJ_SERVER = $(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)

OBJ_BONUS_SERVER = $(SRC_BONUS_SERVER:%.c=$(OBJ_BONUS_DIR)/%.o)
OBJ_BONUS_CLIENT = $(SRC_BONUS_CLIENT:%.c=$(OBJ_BONUS_DIR)/%.o)

# ==== LIBFT ==== #

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

# ==== RULES ==== #

all : $(LIBFT_A) $(OBJ_DIR) $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(LIBFT_A) $(OBJ_BONUS_DIR) $(NAME_BONUS_CLIENT) $(NAME_BONUS_SERVER)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR) :
	@mkdir -p $(OBJ_BONUS_DIR)

$(LIBFT_A) :
	@echo "Compilation de la libft..."
	@make -s -C $(LIBFT_DIR)

$(NAME_SERVER) : $(OBJ_SERVER) $(LIBFT_A)
	@echo "Link du binaire 'server'..."
	@$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT_A)

$(NAME_CLIENT) : $(OBJ_CLIENT) $(LIBFT_A)
	@echo "Link du binaire 'client'..."
	@$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT_A)

$(NAME_BONUS_SERVER) : $(OBJ_BONUS_SERVER) $(LIBFT_A)
	@echo "Link du binaire 'server'..."
	@$(CC) $(CFLAGS) -o $(NAME_BONUS_SERVER) $(OBJ_BONUS_SERVER) $(LIBFT_A)

$(NAME_BONUS_CLIENT) : $(OBJ_BONUS_CLIENT) $(LIBFT_A)
	@echo "Link du binaire 'client'..."
	@$(CC) $(CFLAGS) -o $(NAME_BONUS_CLIENT) $(OBJ_BONUS_CLIENT) $(LIBFT_A)

$(OBJ_DIR)/%.o: %.c
	@echo "Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: %.c
	@echo "Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo "Suppression des fichiers objets..."
	@make -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean : clean
	@echo "Suppression des exécutables..."
	@make -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_BONUS_SERVER) $(NAME_BONUS_CLIENT)

re : fclean all

.PHONY : all clean fclean re

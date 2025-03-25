
# ==== PROGRAM NAME ==== #

NAME = libftprintf.a

# ==== COMPILER AND FLAGS ==== #

CC = cc
CFLAGS = -Wall -Werror -Wextra

# ==== CREATE STATIC ARCHIVE ==== #

AR = ar rcs

# ==== FILES ==== #

SRC = ft_printf.c ft_printf_utils.c

OBJ_DIR  = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# ==== RULES ==== #

all : $(OBJ_DIR) $(NAME)

obj :
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
	@echo "📦 Création de $(NAME)..."
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c 
	@echo "🔧 Compilation de $<"
	@$(CC) $(CFAGS) -c $< -o $@

clean:
	@echo "🧹 Suppression des fichiers objets..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🧨 Suppression des exécutables..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
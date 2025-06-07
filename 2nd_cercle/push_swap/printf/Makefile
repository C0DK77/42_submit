
# ==== PROGRAM NAME ==== #

NAME 	= ft_printf.a

# ==== COMPILER AND FLAGS ==== #

CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra

# ==== CREATE STATIC ARCHIVE ==== #

AR 		= ar rcs

# ==== FILES ==== #

SRC 	= 	ft_printf.c \
			ft_printf_utils.c

OBJ_DIR = obj
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== RULES ==== #

all 	: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compilation de $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean	:
	@rm -rf $(OBJ_DIR)

fclean	: clean
	@rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re
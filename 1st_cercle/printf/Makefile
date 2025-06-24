
# ==== PROGRAM NAME ==== #

NAME 				= 	printf.a

# ==== CREATE STATIC ARCHIVE ==== #

AR 					=	ar rcs

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror					

# ==== FILES ==== #

SRC 				= 	ft_printf.c ft_printf_utils.c

OBJ_DIR 			= 	obj
OBJ 				= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== RULES ==== #

all					: 	$(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(AR) $@ $^

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

clean 				:
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re


# ==== PROGRAM NAME ==== #

NAME 				= 	printf.a

# ==== CREATE STATIC ARCHIVE ==== #

AR 					=	ar rcs

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror	\
						-I. 					\
						-I$(LIBFT_DIR) 				

# ==== FILES ==== #

SRC 				= 	ft_printf.c ft_printf_utils.c 

OBJ_DIR 			= 	obj
OBJ 				= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT ==== #

LIBFT_DIR			= 	./libft
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a 

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A)

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) 			:
					  	@make -s -C $(LIBFT_DIR)
					  	@make bonus -s -C $(LIBFT_DIR)

clean 				:
					  	@make -s -C $(LIBFT_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re

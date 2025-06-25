
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell.a

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror		\
						-I.						 	\
						-I$(PRINTF_DIR) 			\
						-I$(LIBFT_DIR) 				\
						-I/usr/include/readline 	

# ==== FILES ==== #

SRC 				= 	main.c 
OBJ_DIR 			= 	obj

OBJ 				= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT / PRINTF /	GET NEXT LINE ==== #

LIBFT_DIR			= 	./libft
PRINTF_DIR 			= 	./printf

LIBFT_A 			= 	$(LIBFT_DIR)/libft.a
PRINTF_A 			= 	$(PRINTF_DIR)/ft_printf.a

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(PRINTF_A) $(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A) $(PRINTF_A)

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) 			:
					  	@make -s -C $(LIBFT_DIR)

$(PRINTF_A) 		:
					  	@make -s -C $(PRINTF_DIR)

clean 				:
					  	@make -s -C $(LIBFT_DIR) clean
					  	@make -s -C $(PRINTF_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@make -s -C $(PRINTF_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re

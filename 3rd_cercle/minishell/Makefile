
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell.a

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror		\
						-I.						 	\
						-I$(LIBFT_DIR)

# ==== FILES ==== #

SRC 				= 	main.c parse.c var.c var_utils.c token.c token_utils.c exec.c exec_utils.c functions.c print.c
OBJ_DIR 			= 	obj

OBJ 				= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== READLINE ==== #

CPPFLAGS			= 	-I/opt/homebrew/opt/readline/include
LDFLAGS				=	-L/opt/homebrew/opt/readline/lib -lreadline

# ==== LIBFT / PRINTF /	GET NEXT LINE ==== #

LIBFT_DIR			= 	./libft
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(NAME)

$(NAME) 			: 	$(OBJ)
						@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBFT_A) $(LDFLAGS)

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT_A) 			:
					  	@make -s -C $(LIBFT_DIR)

clean 				:
					  	@make -s -C $(LIBFT_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re

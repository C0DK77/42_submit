
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror		\
						-I.						 	\
						-I$(LIBFT_DIR)

# ==== FILES ==== #

SRC 				= 	main.c var.c var_utils.c token.c token_utils.c exec.c exec_utils.c print.c signals.c

BUILTINS 			= builtins/ft_exit.c builtins/ft_env.c \
					builtins/ft_export.c builtins/ft_echo.c \
					builtins/ft_unset.c builtins/ft_pwd.c\
					builtins/ft_cd.c builtins/functions.c 

PARSER 				= parser/parse.c 
						
OBJ_DIR 			= 	obj
SRC					+= $(BUILTINS) $(PARSER)

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
						@echo "DEBUG: OBJ_DIR is '$(OBJ_DIR)'"
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

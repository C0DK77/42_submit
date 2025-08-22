
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror							\
						-I.						 						\
						-I$(LIBFT_DIR)

# ==== FILES ==== #

BUILTINS 			= srcs/builtins/ft_exit.c srcs/builtins/ft_env.c \
					srcs/builtins/ft_export.c srcs/builtins/export_utils.c srcs/builtins/ft_echo.c \
					srcs/builtins/ft_unset.c srcs/builtins/ft_pwd.c\
					srcs/builtins/ft_cd.c srcs/builtins/functions.c 

EXEC				= srcs/exec/exec_utils.c srcs/exec/exec.c

ENVIRONNEMENT		= srcs/environnement/env_utils.c \
					srcs/environnement/env_prompt_and_list_init.c\
					srcs/environnement/env_vars_init.c

PARSER 				= srcs/parser/parse.c srcs/parser/parse_utils.c

TOKEN 				= srcs/token/token_operator_utils.c srcs/token/token_utils.c\
					srcs/token/token_word_utils.c srcs/token/token.c
						
OBJ_DIR 			= 	obj

SRC					= main.c signals.c print.c $(BUILTINS) $(ENVIRONNEMENT) $(EXEC) $(PARSER) $(TOKEN)

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
						@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $(NAME)

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

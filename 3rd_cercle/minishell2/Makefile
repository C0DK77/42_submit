
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror							\
						-I.						 						\
						-I$(LIBFT_DIR)

# ==== FILES ==== #

SRC 				= 	program/environment/env_prompt_and_list_init.c	\
						program/environment/env_vars_init.c 			\
						program/environment/env_utils.c 				\
						program/environment/env_init.c 				\
						program/token/token_check.c 					\
						program/token/token_list.c	 					\
						program/token/token_utils.c 					\
						program/token/token_operator_utils.c 			\
						program/token/token_word_utils.c 				\
						program/token/token.c			 				\
						program/parse/parse_heredoc.c 					\
						program/parse/parse_utils.c 					\
						program/parse/parse_redir.c 					\
						program/parse/parse.c			 				\
						program/exec/exec.c		 						\
						program/exec/exec_cmd.c 						\
						program/exec/exec_create_here.c 				\
						program/exec/exec_env_array.c 					\
						program/exec/exec_redir_init.c 					\
						program/exec/exec_utils.c 						\
						program/functions/echo.c 						\
						program/functions/pwd.c							\
						program/functions/pwd_utils.c					\
						program/functions/env.c 						\
						program/functions/exit.c						\
						program/functions/unset.c						\
						program/functions/unset_utils.c					\
						program/functions/export.c						\
						program/functions/export_utils.c				\
						program/functions/functions.c					\
						program/functions/cd.c							\
						program/functions/cd_utils.c					\
						program/signals/signals.c						\
						main.c
						
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

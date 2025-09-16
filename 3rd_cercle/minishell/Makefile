
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror -g3 -I. \
						-I$(LIBFT_DIR)

READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null)
ifeq ($(READLINE_PREFIX),)
  READLINE_PREFIX := /opt/homebrew/opt/readline
endif

CPPFLAGS 			+= -I$(READLINE_PREFIX)/include
LDFLAGS  			+= -L$(READLINE_PREFIX)/lib -Wl,-rpath,$(READLINE_PREFIX)/lib
LDLIBS   			+= -lreadline -lncurses 

# ==== FILES ==== #

BUILTINS 			= srcs/builtins/ft_exit.c srcs/builtins/ft_env.c \
					srcs/builtins/ft_export.c srcs/builtins/export_utils.c srcs/builtins/ft_echo.c \
					srcs/builtins/ft_unset.c srcs/builtins/unset_utils.c \
					srcs/builtins/pwd_utils.c srcs/builtins/ft_pwd.c \
					srcs/builtins/cd_utils.c srcs/builtins/ft_cd.c srcs/builtins/ft_exec_builtins.c 

ENVIRONNEMENT		= srcs/environnement/env_utils.c \
					srcs/environnement/env_prompt_and_list_init.c\
					srcs/environnement/env_vars_init.c

EXEC				= srcs/execution/exec_utils.c srcs/execution/exec.c

SIGNALS				= srcs/signals/signals.c

PARSER 				= srcs/parser/parse_core.c srcs/parser/parse_utils.c srcs/parser/parse_heredoc.c srcs/parser/parse_redir.c

LEXER 				= srcs/lexer/token_check.c srcs/lexer/token_dollar.c srcs/lexer/token_list.c\
					srcs/lexer/token_word_scan.c srcs/lexer/tokenize.c srcs/lexer/utils.c
						
OBJ_DIR 			= 	obj

SRC					= main.c $(BUILTINS) $(ENVIRONNEMENT) $(EXEC) $(PARSER) $(LEXER) $(SIGNALS)

OBJ 				= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT ==== #

LIBFT_DIR			= 	./libft
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(NAME)

$(NAME) 			: 	$(OBJ)
						@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) $(LDLIBS) -o $@

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

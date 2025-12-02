
# ==== PROGRAM NAME ==== #

NAME 				= 	minishell

# ==== FLAGS AND COMPILER ==== #

CC 					= 	cc
CFLAGS 				= 	-Wall -Wextra -Werror							\
						-MMD -MP -I.						 			\
						-I$(LIBFT_DIR)


# LINUX
CFLAGS 			:= 	-Wall -Wextra -Werror -MMD -MP -I. -ILibft
LDFLAGS 			:= 	-lreadline

# MAC 
# BREW_PREFIX 	:= 	$(shell brew --prefix 2>/dev/null || echo /usr/local)
# CPPFLAGS 		:= 	-I$(BREW_PREFIX)/opt/readline/include
# LDFLAGS 		:= 	-L$(BREW_PREFIX)/opt/readline/lib -lreadline

LIBFT_DIR 		:= 	Libft
LIBFT 			:= 	$(LIBFT_DIR)/libft.a

SRC 			:= 	main.c 							\
					0_env/env.c 					\
					0_env/signals.c 				\
					0_env/utils.c 					\
					1_lexer/lexer.c 				\
					1_lexer/utils.c 				\
					2_token/token.c   				\
					2_token/utils_1.c 				\
					2_token/utils_2.c 				\
					3_parser/parser.c 				\
					3_parser/utils_1.c 				\
					3_parser/utils_2.c 				\
					4_expander/expander.c 			\
					4_expander/utils_1.c 			\
					4_expander/utils_2.c 			\
					4_expander/utils_3.c 			\
					5_commandes/cd_utils.c 			\
					5_commandes/cd.c 				\
					5_commandes/echo.c 				\
					5_commandes/env.c 				\
					5_commandes/exit.c 				\
					5_commandes/export_utils.c 		\
					5_commandes/export.c 			\
					5_commandes/unset.c 			\
					5_commandes/pwd.c 				\
					6_exec/exec.c 					\
					6_exec/utils_1.c 				\
					6_exec/utils_2.c 				\
					6_exec/utils_3.c 				\
					6_exec/utils_4.c 				\
					7_redir/heredoc.c 				\
					7_redir/redir.c 				\
					7_redir/utils.c 				\
					8_utils/free_1.c 				\
					8_utils/free_2.c 				\
					8_utils/utils_list.c 					


OBJ_DIR 			= 	obj

OBJ 				= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT ==== #

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

test				:	all
						@echo "🚀 Lancement du script de test..."
						@bash test/test_minishell.sh

clean 				:
					  	@make -s -C $(LIBFT_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re test

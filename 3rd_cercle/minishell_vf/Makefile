
NAME_EXEC 		:= 	minishell

CC 				:= 	cc

CFLAGS 			:= 	-Wall -Wextra -Werror -MMD -MP -I. -ILibft
LDFLAGS 		:= 	-lreadline

LIBFT_DIR 		:= 	Libft
LIBFT 			:= 	$(LIBFT_DIR)/libft.a

SRC_TEST_EXEC 	:= 	main.c 							\
					0_env/env.c 					\
					0_env/signals.c 				\
					0_env/utils.c 					\
					1_lexer/lexer.c 				\
					1_lexer/utils.c 				\
					2_tokenizer/token.c   			\
					2_tokenizer/utils_1.c 			\
					2_tokenizer/utils_2.c 			\
					3_parser/parser.c 				\
					3_parser/utils_1.c 				\
					3_parser/utils_2.c 				\
					4_expander/expander.c 			\
					4_expander/utils_1.c 			\
					4_expander/utils_2.c 			\
					4_expander/utils_3.c 			\
					4_expander/utils_4.c 			\
					5_commandes/cd_utils.c 			\
					5_commandes/cd.c 				\
					5_commandes/echo.c 				\
					5_commandes/env.c 				\
					5_commandes/exit.c 				\
					5_commandes/export_utils.c 		\
					5_commandes/export.c 			\
					5_commandes/unset.c 			\
					5_commandes/pwd.c 				\
					5_exec/exec.c 					\
					5_exec/heredoc.c 				\
					5_exec/redir.c 					\
					5_exec/builtins/echo.c 			\
					5_exec/builtins/cd.c 			\
					5_exec/builtins/pwd.c 			\
					5_exec/builtins/export.c 		\
					5_exec/builtins/unset.c 		\
					5_exec/builtins/env.c 			\
					5_exec/builtins/exit.c 			\
					5_exec/norme/redir_norme.c 		\
					5_exec/norme/redir_norme2.c 	\
					5_exec/norme/unset_norme.c 		\
					5_exec/norme/exit_norme.c 		\
					5_exec/norme/export_norme.c 	\
					5_exec/norme/export_norme2.c	\
					5_exec/norme/cd_norme.c 		\
					5_exec/norme/exec_norme.c 		\
					5_exec/norme/exec_norme2.c 		\
					5_exec/norme/exec_norme3.c 		\
					5_exec/norme/exec_norme4.c 		\
					5_exec/norme/exec_norme5.c		\
					5_exec/norme/exec_norme6.c 		\
					5_exec/norme/exec_norme7.c		\
					6_free/free.c 					\
					6_free/free2.c 					\
					6_free/error.c 					


OBJDIR 			:= 	obj
OBJDIR_TEXEC 	:= 	$(OBJDIR)/test_exec
OBJS_TEXEC 		:= 	$(SRC_TEST_EXEC:%.c=$(OBJDIR_TEXEC)/%.o)

DEPS 			:= 	$(OBJS_TEXEC:.o=.d)

.PHONY			: 
					all clean fclean re test-lexer test-tokenizer test-parser test-expander test-exec

all				: 	$(NAME_EXEC)

$(LIBFT)		:
					$(MAKE) -C $(LIBFT_DIR)

test-exec		: 	$(NAME_EXEC)
$(NAME_EXEC)	: 	$(LIBFT) $(OBJS_TEXEC)
					$(CC) $(CFLAGS) $(OBJS_TEXEC) $(LIBFT) -o $@ $(LDFLAGS)

$(OBJDIR_TEXEC)/%.o: %.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					rm -rf $(OBJDIR)
					$(MAKE) -C $(LIBFT_DIR) clean

fclean			: 	clean
					rm -f $(NAME_EXEC)
					$(MAKE) -C $(LIBFT_DIR) fclean

re				: 	fclean all

-include $(DEPS)

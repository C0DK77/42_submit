/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/07 21:50:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//	STRUCTURE ENV

typedef struct s_envp
{
	char				*var;
	char				*value;
	struct s_envp		*next;
}						t_envp;

//	STRUCTURE VAR

typedef struct s_var
{
	char				*var;
}						t_var;

extern t_var			g_vars_to_check[];

//	STRUCTURE TOKEN

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SEMICOLON,
	TOKEN_AND,
	TOKEN_AND_IF,
	TOKEN_OR,
	TOKEN_OR_IF,
	TOKEN_BACKGROUND,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_EOF
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

extern int				g_exit_status;

//	STRUCTURE PARSING

typedef enum s_sep
{
	SEP_NONE,
	SEP_PIPE,
	SEP_AND,
	SEP_AND_IF,
	SEP_OR,
	SEP_OR_IF,
	SEP_SEQ,
	SEP_BACKGROUND
}						t_sep;

typedef struct s_parsing
{
	char				**line;
	char				*infile;
	char				*outfile;
	int					append;
	int					heredoc;
	t_sep				sep;
	struct s_parsing	*next;
}						t_parsing;

//	ENV / UTILS

char					*ft_prompt(void);
t_envp					*ft_create_envp(char *str);
t_envp					*ft_init_envp(char **envp);
t_envp					*ft_search_var(t_envp *lst, char *var);
void					ft_free_envp(t_envp *lst);

//	ENV / VAR

int						ft_check_all_var(t_envp **envp);
int						ft_check_var(t_envp **envp, char *var);
int						ft_change_var(t_envp **envp, t_envp *t, char *var);
int						shlvl(t_envp *t);

//	TOKEN / PARSE

t_token					*ft_parse_line(char *str, t_envp *envp);
int						ft_parse_word_double_quotes(t_envp *envp, char **word,
							char *line, int end, int i);
int						ft_parse_dollar_sign(t_envp *envp, char **word,
							char *line, int i);
int						ft_parse_word_without_quotes(char **word, char *line,
							int i);
int						ft_parse_word_single_quote(char **word, char *line,
							int i, int start);
int						ft_parse_word(t_token **lst, char *line, int i,
							t_envp *envp);
int						ft_parse_operator(t_token **lst, char *line, int i);

//	TOKEN / UTILS

t_token					*ft_create_token(t_token_type type, char *value);
void					ft_add_token(t_token **head, t_token *new_token);
void					ft_free_token(t_token *lst);
void					ft_print_token(t_token *lst);

//	PARSE / PARSE

t_parsing				*ft_parsing_line(t_token *t);

//	PARSE / UTILS

char					**ft_append_token(char **line, char *value);
void					ft_print_parsing(t_parsing *lst);

#endif

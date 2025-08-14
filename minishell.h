/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/14 15:50:16 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HEREDOC_FILE "/tmp/.minishell_heredoc"
extern struct s_history	*g_history;

/* global*/
extern int				g_exit_status;

//	STRUCTURE ENV

typedef struct s_envp
{
	char				*var;
	char				*value;
	int					export;
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
	WRD,
	PIPE,
	R_IN,
	R_OUT,
	R_APPEND,
	HERE,
	SEMIC,
	AND,
	AND_IF,
	OR,
	OR_IF,
	BACKGRD,
	O_PAREN,
	C_PAREN
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

//	STRUCTURE PARSING

typedef enum s_sep
{
	SEP_NONE = 0,
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
	struct s_parsing	*prev;
}						t_parsing;

//	STRUCTURE HISTORIQUE

typedef struct s_history
{
	char				*line;
	struct s_history	*next;
}						t_history;

//	ENV / UTILS

char					*ft_env_prompt(void);
t_envp					*ft_env_copy(char *s);
t_envp					*ft_env_init(char **l);
char					*ft_env_search_value(t_envp *l, char *v);
t_envp					*ft_env_search_node(t_envp *l, char *v);
void					ft_env_free(t_envp *l);

//	ENV / VAR

int						ft_vars_check(t_envp **l);
int						ft_var_check(t_envp **l, char *v);
int						ft_var_init(t_envp **l, t_envp *t, char *v);
int						ft_var_shlvl(t_envp *l);

//	TOKEN / PARSE

int						ft_token_word_dbquote(t_envp *l, char **w, char *s,
							int z, int i);
int						ft_token_ope_dollar(t_envp *l, char **w, char *s,
							int i);
int						ft_token_word_noquote(char **w, char *s, int i);
int						ft_token_word_sgquote(char **w, char *s, int i, int j);
int						ft_token_word(t_token **n, char *s, int i, t_envp *l);
int						ft_token_ope(t_token **l, char *s, int i);

//	TOKEN / UTILS

t_token					*ft_token_init(t_token_type t, char *v);
void					ft_token_add(t_token **l, t_token *n);
t_token					*ft_token(char *s, t_envp *l);
int						ft_token_check(t_token *n);
void					ft_token_free(t_token *l);

//	PARSE / PARSE

char					**ft_parse_add(char **line, char *value);
t_parsing				*ft_parse_line(t_token *t);

//	EXEC / UTILS

int						ft_exec_redirections_init(t_parsing *s);
int						ft_exec_create_heredoc(char *delimiter);
int						ft_exec_is_directory(char *p);
char					*ft_exec_find_cmd(char *s, t_envp *l);
char					*ft_strjoin_three(char *s1, char *s2, char *s3);
void					ft_free_split(char **arr);
char					**ft_env_to_tab(t_envp *l);
void					ft_env_set(t_envp **l, char *s, char *value, int i);
void					ft_env_sorted(t_envp *envp);

//	EXEC / EXEC

void					ft_exec(t_parsing *p, t_envp *l);
void					ft_exec_cmd(char **s, t_envp *l);
char					**ft_exec_env_array(t_envp *l);

//	FUNCTIONS

void					ft_exec_cmd(char **s, t_envp *l);
int						ft_exec_builtin(char **s, t_envp **l);
int						ft_echo(char **s);
int						ft_exit(char **s);
int						ft_pwd(char **s, t_envp *l);
int						ft_env(t_envp *l);
int						ft_cd(char **s, t_envp *l);
int						ft_export(char **s, t_envp **envp);
int						ft_unset(char **s, t_envp **envp);
void					ft_history_add(t_history **h, const char *s);
void					ft_history_print(t_history *h);
void					ft_history_clear(t_history **h);
int						parse_pwd_opts(char **s, int *p);
void					update_pwd_vars(t_envp *l, char *s);

void					ft_print_token(t_token *l);
void					ft_print_parsing(t_parsing *lst);

/*SIGNAUX*/

void					reset_signals(void);
void					ft_sigint_handler(int sig);
void					setup_signals(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 20:57:48 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

# define HEREDOC_FILE "/tmp/.minishell_heredoc"
extern struct s_history	*g_history;

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

extern int				g_exit_status;

//	STRUCTURE OPERATOR

typedef struct s_operator
{
	char				*s;
	int					type;
}						t_operator;

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

//	ENVIRONMENT / ENV_PROMPT_AND_LIST_INIT

char					*ft_env_prompt(void);
t_envp					*ft_env_list_init(char **l);
t_envp					*ft_env_var_copy(char *s);

//	ENVIRONMENT / ENV_UTILS

char					*ft_env_search_value(t_envp *l, char *v);
t_envp					*ft_env_search_node(t_envp *l, char *v);
void					ft_env_free(t_envp *l);
void					ft_free_all(int argc, ...);

//	ENVIRONMENT / ENV_VARS_INIT

t_var					*ft_env_vars_init_table(void);
int						ft_env_vars_check(t_envp **l);
int						ft_env_list_var_check(t_envp **l, char *v);
int						ft_env_vars_create(t_envp **l, t_envp *t, char *v);
int						ft_var_increase_shlvl(t_envp *l);

//	TOKEN / TOKEN_LIST_UTILS

t_token					*ft_token_init(t_token_type t, char *v);
void					ft_token_add(t_token **l, t_token *n);
void					ft_token_free(t_token *l);

//	TOKEN / TOKEN_OPE_UTILS

t_operator				*ft_token_ope_init_table(void);
char					*ft_token_ope_dollar(t_envp *l, char **w, char *s);
char					*ft_token_ope(t_token **l, char *s);

//	TOKEN / TOKEN_WORD_UTILS

char					*ft_token_word_dbquote(t_envp *l, char **w, char *s,
							int end);
char					*ft_token_word_noquote(char **w, char *s);
char					*ft_token_word_sgquote(char **w, char *s, int i);
char					*ft_token_word(t_token **n, char *s, t_envp *l);

//	TOKEN / UTILS

t_token					*ft_token(char *s, t_envp *l);
int						ft_token_check(t_token *n);

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
void					ft_sigint_handler(int sig);
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
int						program(int argc, char **argv, t_envp *c_envp);

#endif

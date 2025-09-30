/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/30 18:38:03 by codk             ###   ########.fr       */
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
# include <sys/wait.h>
# include <unistd.h>

# define HEREDOC_FILE "/tmp/.minishell_heredoc"

extern volatile sig_atomic_t	g_exit_status;

//	STRUCTURE ENV

typedef struct s_envp
{
	char						*var;
	char						*value;
	int							export;
	struct s_envp				*next;
}								t_envp;

//	STRUCTURE VAR

typedef struct s_var
{
	char						*var;
}								t_var;

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
}								t_token_type;

//	STRUCTURE TOKEN

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	int							quoted;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

//	STRUCTURE OPERATOR

typedef struct s_operator
{
	char						*s;
	int							type;
}								t_operator;

//	STRUCTURE SEPARATOR

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
}								t_sep;

//	STRUCTURE PARSING

typedef struct s_parsing
{
	char						**line;
	char						**infiles;
	char						**outfiles;
	int							*append;
	int							heredoc;
	int							heredoc_fd;
	int							heredoc_expand;
	t_sep						sep;
	struct s_parsing			*next;
	struct s_parsing			*prev;
}								t_parsing;

//	MAIN

int								ft_program(t_envp *c_envp);
char							*ft_program_check_unclosed_quote(char *line);

//	ENVIRONMENT / ENV_PROMPT_AND_LIST_INIT

char							*ft_env_prompt(void);
t_envp							*ft_env_list_init(char **l);
t_envp							*ft_env_var_copy(char *s);

//	ENVIRONMENT / ENV_UTILS

char							*ft_env_search_value(t_envp *l, char *v);
t_envp							*ft_env_search_node(t_envp *l, char *v);
void							ft_env_free(t_envp *l);
void							ft_free_all(int argc, ...);
int								ft_env_add_value(t_envp **l, char *s, char *v,
									int i);

//	ENVIRONMENT / ENV_VARS_INIT

t_var							*ft_env_vars_init_table(void);
int								ft_env_vars_check(t_envp **l);
int								ft_env_list_var_check(t_envp **l, char *v);
int								ft_env_vars_create(t_envp **l, t_envp *t,
									char *v);
int								ft_var_increase_shlvl(t_envp *l);

//	TOKEN / TOKEN_UTILS

char							*ft_token_isquote(t_envp *env, char **w,
									char *s);
int								ft_token_check(t_token *token);
int								ft_token_check_bis(t_token *token, t_token *p,
									int i);

//	TOKEN / TOKEN_OPERATOR_UTILS

char							*ft_token_ope_dollar(t_envp *env, char **w,
									char *s);
char							*ft_token_ope(t_token **env, char *s);
char							*ft_token_ope_dollar_interrogation(char **w,
									char *s);
char							*ft_token_ope_dollar_word(char *s);
char							*ft_token_ope_dollar_no_word(char **w, char *s);

//	TOKEN / TOKEN

t_operator						*ft_token_ope_init_table(void);
t_token							*ft_token(t_envp *env, char *s);
t_token							*ft_token_init(t_token_type type, char *v,
									int i);
void							ft_token_add(t_token **token, t_token *n);
void							ft_token_free(t_token *token);

//	TOKEN / TOKEN_WORD_UTILS

char							*ft_token_word_dbquote(t_envp *env, char **w,
									char *s, char *end);
char							*ft_token_word_noquote(char **w, char *s);
char							*ft_token_word_sgquote(char **w, char *s,
									char *i);
int								ft_token_word_len(char *s);
char							*ft_token_word(t_envp *env, t_token **token,
									char *s);

//	PARSE / PARSE

t_parsing						*ft_parse_line(t_envp *env, t_token *token);
void							ft_parse_type(t_token *token, t_parsing *parse);
void							ft_redirection_type(t_envp *env,
									t_parsing *parse, char *s, int i);
int								ft_handle_redirection(t_envp *env,
									t_token **token, t_parsing *parse);

//	PARSE / PARSE_UTILS

char							**ft_parse_add_value(char **s, char *v);
t_parsing						*ft_parse_add_node(t_parsing **n, t_parsing **p,
									t_parsing **a);
int								*ft_parse_add_append(int *s, int a);

//	EXEC / EXEC_UTILS

int								ft_exec_redirections_init(t_parsing *s);
int								ft_exec_heredoc(t_parsing *s, int i);
int								ft_exec_create_heredoc(char *delimiter);
int								ft_exec_is_directory(char *p);
char							*ft_exec_find_cmd(char *s, t_envp *l);

//	EXEC / EXEC

void							ft_exec(t_parsing *p, t_envp *l);
void							ft_exec_cmd(char **s, t_envp *l);
char							**ft_exec_env_array(t_envp *l);

//	FUNCTIONS / FUNCTIONS

int								ft_exec_builtin(char **s, t_envp **l);
int								ft_exec_builtin_bis(char **s, t_envp **l);

//	FUNCTIONS / PWD

int								ft_pwd(char **s, t_envp *l);
char							**ft_pwd_check_options(char **s, int *p);
int								ft_pwd_options(char *pwd, int o);
char							**ft_pwd_put_options(char **s, int *p);
int								ft_pwd_error(int i, int c);

//	FUNCTIONS / PWD_UTILS

void							ft_pwd_update_vars(t_envp *l, char *s);
void							ft_pwd_export_env_set(t_envp **l, char *s,
									char *v, int i);
void							ft_env_update_existing(t_envp *e, char *v,
									int i);
t_envp							*ft_env_new_pair(char *name, char *val, int i);
void							ft_env_append(t_envp **l, t_envp *n);

//	FUNCTIONS / ECHO

int								ft_echo(char **s);
int								ft_echo_option(char *arg);

//	FUNCTIONS / EXIT

int								ft_exit(char **s);

//	FUNCTIONS / ENV

int								ft_env(t_envp *l);

//	FUNCTIONS / CD

int								ft_cd(char **s, t_envp *l);
char							*ft_cd_conditions(char **s, t_envp *l, int i);
int								ft_cd_search_var(t_envp *l, char *v);
char							*ft_cd_error(int i, char *c);

//	FUNCTIONS / UNSET

int								ft_unset(char **s, t_envp **l);
int								ft_unset_check_identifier(char *s);
void							ft_unset_change(char **s, t_envp **l);
int								ft_unset_error(int i, char *s);

//	FUNCTIONS / EXPORT

int								ft_export(char **s, t_envp **e);
int								ft_export_no_arguments(t_envp **l);
int								ft_export_arguments(char **s, t_envp **l,
									char *a);
int								ft_export_check_valid_var(char *s, int *i);
int								ft_export_error(char *t);

//	FUNCTIONS / EXPORT_UTILS

int								ft_export_check_value(t_envp **l, char *n,
									char *a, int i);
int								ft_export_value(t_envp **l, char *v, char *n,
									int *i);

char							*ft_expand_variables(char *line, t_envp *e);
void							ft_parse_heredoc(t_envp *env, t_parsing *parse,
									char *s);
int								is_quoted(char *s);
char							*remove_quotes(char *s);

//	SIGNALS / SIGNALS

void							ft_sigint_handler(int sig);
void							ft_handler_exec(int sig);
void							setup_signals(void);
void							reset_signals(void);

void							print_tokens(t_token *t);
void							print_parsing(t_parsing *p);

#endif

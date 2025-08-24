/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:10:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/24 16:57:26 by ecid             ###   ########.fr       */
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
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define HEREDOC_FILE "/tmp/.minishell_heredoc"

extern int				g_exit_status;

//  STRUCTURE ENV
typedef struct s_envp
{
	char				*var;
	char				*value;
	int					export;
	struct s_envp		*next;
}						t_envp;

//  STRUCTURE VAR
typedef struct s_var
{
	char				*var;
}						t_var;

//  STRUCTURE TOKEN
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

//  STRUCTURE OPERATOR
typedef struct s_operator
{
	char				*s;
	int					type;
}						t_operator;

//  STRUCTURES PARSING
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
	char				**infiles;
	char				**outfiles;
	int					*append;
	int					heredoc;
	t_sep				sep;
	struct s_parsing	*next;
	struct s_parsing	*prev;
}						t_parsing;

//  STRUCTURE HISTORIQUE
typedef struct s_history
{
	char				*line;
	struct s_history	*next;
}						t_history;

/*------------------- MAIN -------------------*/

int						ft_program(t_envp *c_envp);

/*------------------- ENVIRONMENT -------------------*/

char					*ft_env_prompt(void);
t_envp					*ft_env_list_init(char **l);
t_envp					*ft_env_var_copy(char *s);
t_var					*ft_env_vars_init_table(void);
int						ft_env_add_value(t_envp **l, char *s, char *v, int i);
int						ft_env_vars_check(t_envp **l);
int						ft_env_list_var_check(t_envp **l, char *v);
int						ft_env_vars_create(t_envp **l, t_envp *t, char *v);
int						ft_var_increase_shlvl(t_envp *l);
char					*ft_env_search_value(t_envp *l, char *v);
t_envp					*ft_env_search_node(t_envp *l, char *v);
void					ft_env_free(t_envp *l);
void					ft_free_all(int argc, ...);

/* ------------------- PARSER ------------------- */

t_parsing				*ft_parse_line(t_token *t);
void					ft_parse_type(t_parsing *n, t_token *t);
int						*ft_parse_add_append(int *s, int a);
void					ft_redirection_type(t_parsing *n, int t, char *f);
int						ft_handle_redirection(t_parsing *n, t_token **t);
char					**ft_parse_add_value(char **s, char *v);
t_parsing				*ft_parse_add_node(t_parsing **n, t_parsing **p,
							t_parsing **a);

/* ------------------- EXECUTION ------------------- */

int						ft_exec_redirections_init(t_parsing *s);
int						ft_exec_create_heredoc(char *delimiter);
int						ft_exec_is_directory(char *p);
char					*ft_exec_find_cmd(char *s, t_envp *l);
char					*ft_strjoin_three(char *s1, char *s2, char *s3);
void					ft_exec(t_parsing *p, t_envp *l);
void					ft_exec_cmd(char **s, t_envp *l);
char					**ft_exec_env_array(t_envp *l);

/*------------------- BUILTINS -------------------*/

int						ft_exec_builtin(char **s, t_envp **l);
int						ft_echo(char **s);
int						ft_exit(char **s);

// cd
int						ft_cd(char **s, t_envp *l);
char					*ft_cd_conditions(char **s, t_envp *l, char *target,
							int i);
int						ft_cd_search_var(t_envp *l, char *v);
char					*ft_cd_error(int i, char *c);

// pwd
int						ft_pwd(char **s, t_envp *l);
char					**ft_pwd_check_options(char **s, int *p);
int						ft_pwd_options(char *pwd, int o);
char					**ft_pwd_put_options(char **s, int *p);
int						ft_pwd_error(int i, int c);
void					ft_pwd_export_env_set(t_envp **l, char *s, char *v,
							int i);

// unset
int						ft_unset(char **s, t_envp **l);
int						ft_unset_error(int i, char *s);
int						ft_unset_check_identifier(char **s);
void					ft_unset_change(char **s, t_envp **l);
void					update_pwd_vars(t_envp *l, char *s);

// export
int						ft_export(char **s, t_envp **envp);
int						ft_export_no_arguments(t_envp **l);
int						ft_export_arguments(char **s, t_envp **l, char *a);
int						ft_export_check_valid_var(char *s, int *i);
int						ft_export_error(char *t);
int						ft_export_check_value(t_envp **l, char *n, char *a,
							int i);

// env (Ajouté car il manquait)
int						ft_env(t_envp *l);

/*------------------- TOKENIZER -------------------*/

t_token					*ft_token(char *s, t_envp *l);
t_token					*ft_token_init(t_token_type t, char *v);
void					ft_token_add(t_token **l, t_token *n);
void					ft_token_free(t_token *l);
t_operator				*ft_token_operator_init_table(void);
char					*ft_token_operator(t_token **l, char *s);
char					*ft_token_operator_dollar(t_envp *l, char **w, char *s);
char					*ft_token_operator_dollar_interrogation(char **w,
							char *s);
char					*ft_token_operator_dollar_word(char *s);
char					*ft_token_operator_dollar_no_word(char **w, char *s);
int						ft_token_check(t_token *n);
int						ft_token_check_rin_rout_rappend_here(t_token *n);
char					*ft_token_word(t_token **n, char *s, t_envp *l);
char					*ft_token_isquote(t_envp *l, char **w, char *s);
char					*ft_token_word_dbquote(t_envp *l, char **w, char *s,
							char *end);
char					*ft_token_word_sgquote(char **w, char *s, char *i);
char					*ft_token_word_noquote(char **w, char *s);
int						ft_token_word_len(char *s);

/* ------------------- SIGNALS ------------------- */

void					ft_sigint_handler(int sig);
void					setup_signals(void);
void					reset_signals(void);

#endif
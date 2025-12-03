/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:44:32 by codk              #+#    #+#             */
/*   Updated: 2025/12/03 12:19:58 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define SYNTAX "minishell: syntax error near unexpected token"
# define EXIT "minishell: exit: "
# define WARNING "warning: here-document delimited by end-of-file (wanted `"

extern int				g_signal_received;

typedef enum e_type
{
	LITERAL,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	APPEND,
	DOLLAR,
	SPECIAL_VARIABLE,
	EMPTY_CMD,
	UNKNOWN,
}						t_type;

typedef enum s_ctx
{
	NONE,
	D_QUOTE,
	S_QUOTE,
}						t_ctx;

typedef struct s_character
{
	char				c;
	int					word_id;
	t_type				type;
	t_ctx				context;
	struct s_character	*prev;
	struct s_character	*next;
}						t_character;

typedef struct s_token
{
	char				*str;
	t_type				type;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	t_type				type;
	t_type				target_type;
	char				*target;
	struct s_redir		*next;
}						t_redir;

typedef enum e_cmd
{
	CMD_NONE,
	T_ECHO,
	T_CD,
	T_PWD,
	T_EXPORT,
	T_UNSET,
	T_ENV,
	T_EXIT,
	NOT_BUILTIN,
}						t_type_cmd;

typedef struct s_arg
{
	char				*str;
	t_type				type;
}						t_arg;

typedef enum e_element_kind
{
	ARG,
	REDIR,
}						t_element_kind;

typedef struct s_element
{
	t_element_kind		kind;
	union
	{
		t_redir			*redirs;
		t_arg			*arg;
	} u_;
	struct s_element	*next;
}						t_element;

typedef struct s_command
{
	t_type_cmd			cmd;
	t_element			*element;
	size_t				nb_args;
	int					has_pipe_out;
	struct s_command	*next;
	struct s_command	*previous;
}						t_command;

typedef struct s_shell
{
	char				**env;
	int					last_exit;
	int					shlvl;
	int					empty_var;
}						t_shell;

typedef struct s_all
{
	t_character			*ch;
	t_token				*tk;
	t_command			*cmd;
}						t_all;

typedef struct s_ios
{
	int					in_fd;
	int					out_fd;
}						t_ios;

typedef struct s_launch_ctx
{
	pid_t				*pids;
	int					*out_n;
	t_shell				*sh;
}						t_launch_ctx;

typedef struct s_pipeinfo
{
	int					pfd[2];
	int					need_pipe;
	int					out_wr;
}						t_pipeinfo;

typedef struct s_build_state
{
	t_character			*head;
	t_character			*tail;
	int					word;
}						t_build_state;

typedef struct s_var_pos
{
	char				*name;
	int					start;
	int					end;
}						t_var_pos;

//	MAIN

void					ft_program(t_shell *s);
int						ft_program_bis(char *l, t_shell *s);

// ENV / ENV

int						ft_env_set(char **env, t_shell *s);
char					**ft_env_copy(char **env);
char					**ft_env_init(void);
char					**ft_env_check(char **env, int l);
void					ft_env_init_shlvl(t_shell *s, char *o);

// ENV / SIGNALS

void					ft_signal_init(void);
void					ft_signal_handler(int i);
int						ft_signal_check(void);
int						ft_signal_wait(pid_t *p, int n);
void					ft_signal_reset(void);

// ENV / UTILS

char					*ft_env_search_value(char **env, char *var);
void					ft_env_set_var(char ***env, char *var, char *v);
int						ft_env_replace_var(char ***env, char *var, char *n,
							int j);
void					ft_env_add_var(char ***env, char *n);
int						ft_env_count_var(char **env);

// LEXER / LEXER

t_character				*ft_lexer_init(char *l);
int						ft_lexer_parse_quote(char *l, int *i, t_ctx *ctx,
							t_build_state *b);
int						ft_lexer_parse_space(char *l, int *i, t_ctx ctx,
							t_build_state *b);
int						ft_lexer_parse_context(char c, t_ctx *ctx);
int						ft_lexer_parse_token(char *s, int *i, t_ctx ctx,
							t_build_state *b);

// LEXER / UTILS

int						ft_lexer_empty_str(t_ctx ctx, char a, char b);
t_type					ft_lexer_char_type(char c);
int						ft_lexer_append(t_character **hd, t_character **tl,
							char a, t_ctx ctx);
t_character				*ft_lexer_new_node(char c, t_ctx ctx, t_character *tl);

//	TOKEN / TOKEN

t_token					*ft_token_init(t_character *c);
int						ft_token_add_operator(t_token **hd, t_token **tl,
							t_character **ch);
int						ft_token_add_word(t_token **hd, t_token **tl,
							t_character **ch);
void					ft_token_operator(t_character *c, t_character *n,
							t_type *t, size_t *i);
int						ft_token_noword(t_token **hd, t_token **tl,
							t_character **ch, t_character *t);

//	TOKEN / UTILS 1

void					ft_token_add_word_token(t_token *tk, t_character *ch,
							size_t i);
int						ft_token_dollar(t_character *ch);
int						ft_token_dollar_exp(t_character *c);
int						ft_token_special_var(t_character *word_start);

//	TOKEN / UTILS 2

t_token					*ft_token_add(t_type t, size_t i);
void					ft_token_append(t_token **hd, t_token **tl,
							t_token *tk);
size_t					ft_token_wordlen(t_character *ch);
t_type					ft_token_add_type(t_character *l);

//	PARSER / PARSER

t_command				*ft_parser_init(t_token *t);
int						ft_parser_redir(t_token *tk);
int						ft_parser_pipe(t_token *tk);
int						ft_parser_save(t_command *cmd, t_token *tk);
int						ft_parser_valid_redir(t_token *tk, t_token **next);

//	PARSER / UTILS_1

int						ft_parser_special_tokens(t_token **tk, t_command **cmd);
int						ft_parser_add_redir(t_token **tk, t_command **cmd);
int						ft_parser_handle_pipe(t_token **tk, t_command **cmd);
int						ft_parser_handle_cmd_or_arg(t_token **tk,
							t_command **cmd);
t_element				*ft_parser_create_element_redir(t_type type, char *s,
							t_type target);

//	PARSER / UTILS_2

t_redir					*ft_parser_create_redir(t_type type, char *s,
							t_type target_type);
t_element				*ft_parser_create_element_arg(t_type t, char *s);
int						ft_parser_add_cmd(t_command *cmd, char *s);
int						ft_parser_add_arg(t_command *cmd, t_type type, char *s);
t_type_cmd				ft_parser_cmd(char *s);

//	EXPANDER / EXPANDER

void					ft_expander_init(t_command **cmd, t_shell *sh);
void					ft_expander_cmd(t_command *cmd, t_shell *sh);
void					ft_expander_arg(t_element *lmt, t_shell *sh);
void					ft_expander_redir(t_element *lmt, t_shell *sh);
t_element				*ft_expander_empty_var(t_command *cmd, t_element *e);

//	EXPANDER / UTILS_1

char					*ft_expander_string(t_shell *sh, char *s);
t_var_pos				*ft_expander_var_pos(char *s, int *count);
char					**ft_expander_value(t_shell *sh, t_var_pos *var,
							int count);
char					*ft_expander_string_create(char *a, t_var_pos *var,
							char **val, int i);
int						ft_expander_var_count(char *s);

//	EXPANDER / UTILS_2

int						ft_expander_dollar_pos(char *s, int i, t_var_pos *var);
void					*ft_expander_cleanup_var(t_var_pos *var, int i);
char					*ft_expander_get_var_value(t_shell *sh, char *var);
int						ft_expander_len(char *a, t_var_pos *var, char **s,
							int count);
void					ft_expander_copy_value(char *s, int *i, char *val);

//	EXPANDER / UTILS_3

int						ft_expander_extract_var(char *s, t_var_pos *var, int i,
							int j);
int						ft_expander_len_var(char *s, int j);

//	COMMANDES CD

int						ft_cmd_cd(t_command *cmd, t_shell *sh);
int						ft_cmd_cd_check_arg(t_element *t);
char					*ft_cmd_cd_arg(t_element *lmt, t_shell *sh);
int						ft_cmd_set_env(char ***env, char *var, char *c);
int						ft_cmd_cd_replace(char **env, char *var, char *value);

//	COMMANDES CD UTILS

int						ft_cmd_cd_append(char ***penv, char *var, char *a);
char					*ft_cmd_cd_create(char *var, char *a);

//	COMMANDES ECHO

int						ft_cmd_echo(t_command *cmd, t_shell *s);
int						ft_cmd_echo_arg(char *s);
void					ft_cmd_echo_print_arg(t_element *e);

//	COMMANDES ENV

int						ft_cmd_env(t_command *cmd, t_shell *s);
void					ft_cmd_env_print(char **e);

//	COMMANDES EXIT

int						ft_cmd_exit(t_command *cmd, t_shell *sh, t_all *a);
char					**ft_cmd_exit_arg(t_command *cmd, size_t *argc);
void					ft_cmd_exit_no_arg(char **s, t_shell *sh, t_all *a);
int						ft_cmd_exit_isnum(char *s);
void					ft_cmd_exit_error(char **argv, int i, t_shell *sh,
							t_all *a);

//	COMMANDES EXPORT

int						ft_cmd_export(t_command *cmd, t_shell *sh);
int						ft_cmd_export_print(t_shell *sh, int j, char *a);
int						ft_cmd_export_arg_create(char *a, t_shell *s);
int						ft_cmd_export_arg(char **argv, int i, t_shell *sh);
int						ft_cmd_export_isval(char *s);

//	COMMANDES EXPORT UTILS

int						ft_cmd_export_env(char ***env, char *a, char *s);
char					*ft_cmd_export_make_kv(char *a, char *s);

//	COMMANDES PWD

int						ft_cmd_pwd(t_command *cmd, t_shell *s);

//	COMMANDES UNSET

int						ft_cmd_unset(t_command *cmd, t_shell *s);
int						ft_cmd_unset_arg(char **args, t_shell *s);
int						ft_cmd_unset_isid(char *s);
void					ft_cmd_unset_remove_env(char ***a, char *name);

// EXEC / EXEC

int						ft_exec_init(t_all *all, t_command *cmd, t_shell *sh);
int						ft_exec_cmd_single(t_command *cmd, t_shell *sh,
							t_all *all);
int						ft_exec_cmd_all(t_command *cmd, t_shell *sh, pid_t *p,
							int *out_n);
int						ft_exec_save_stdio(int *saved_in, int *saved_out);
void					ft_exec_restore_stdio_and_close(int saved_in,
							int saved_out);

// EXEC / UTILS_1

int						ft_exec_cmd(t_command *cmd, t_shell *sh, t_all *all);
int						ft_exec_cmd_one(t_command *cmd, int *i,
							t_launch_ctx *ctx);
pid_t					ft_exec_cmd_one_spawn(t_command *cmd, int i, int j,
							t_shell *sh);
void					ft_exec_clean(int *i, t_pipeinfo *pi);
void					ft_exec_pipe_state(int *i, t_pipeinfo *pi);

// EXEC / UTILS_2

int						ft_exec_child_fds(t_command *cmd, int i, int j,
							t_shell *sh);
void					ft_exec_child(t_command *cmd, t_shell *sh, t_all *all);
int						ft_exec_path(char **argv, t_shell *sh);
void					ft_exec_handle_error(char **argv);
int						ft_exec_path_check(char *path, char **argv, t_shell *sh,
							int i);

// EXEC / UTILS_3

char					*ft_exec_path_res(char *cmd, char **env);
int						ft_exec_isdirectory(char *p);
char					*ft_exec_path_dir(char *s, char *cmd);
void					ft_exec_print_error_1(char *path, char *s, int e);
void					ft_exec_print_error_2(char *a, int e);

// EXEC / UTILS_4

void					ft_signal_config_last_exit(t_shell *sh, pid_t *p,
							int i);

// REDIR / REDIR

int						ft_redir_fds(t_element *lmt, t_ios *ios, t_shell *sh);
int						ft_redir_apply_1(t_ios *ios, t_redir *r, t_shell *sh);
int						ft_redir_apply_2(t_ios *ios);
int						ft_redir_apply_3(t_command *cmd, int saved_in,
							int saved_out, t_shell *sh);
void					ft_redir_close(t_ios *ios);

// REDIR / HEREDOC

int						ft_heredoc(char *s, t_shell *sh);
void					ft_heredoc_process(int *fd, char *a);
int						ft_heredoc_status(int status, int fd, t_shell *sh);

// REDIR / UTILS

int						ft_redir_set_in(t_ios *ios, t_redir *r, t_shell *sh);
int						ft_redir_set_out(t_ios *ios, t_redir *r);
int						ft_redir_replace_fd(int *dst, int newfd);
char					*ft_join_path(char *dir, char *cmd);

// UTILS / FREE_1

int						ft_free_program(t_character *c, t_token *t,
							t_command *cmd, int i);
void					ft_free_cmd(t_command *cmd);
void					ft_free_env(t_shell *s);
void					ft_free_char(t_character *c);
void					ft_free_token(t_token *tk);

// UTILS / FREE_2

void					ft_free_redir(t_redir *redir);
void					ft_free_element(t_element *element);
void					ft_free_var(t_var_pos *var, char **a, int count);
void					ft_free_argv(char **argv);
void					ft_debug_parsing(t_character *c, t_token *t,
							t_command *cmd);
void					ft_debug_expander(t_command *cmd);

// UTILS / UTILS LIST

t_all					*ft_init_all(int i);
size_t					ft_count_arg(t_element *e);
void					ft_fill_element(t_element *e, char **argv);
t_element				*ft_element_last_node(t_element *lmt);
int						ft_fill_argv(t_command *cmd, char **argv);

#endif
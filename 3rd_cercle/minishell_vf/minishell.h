/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:44:32 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 06:14:39 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

#define SYNTAX "minishell: syntax error near unexpected token"

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

// ENV / ENV

int						ft_env_set_env(char **env, t_shell *s);
char					**ft_env_copy_env(char **env);
char					**ft_env_init_env(void);
char					**ft_env_check(char **env, int l);

// ENV / SIGNALS

void					ft_signal_init(void);
void					ft_signal_handler(int i);
int						ft_signal_check(void);
void					ft_signal_reset(void);

// ENV / UTILS 1

char					*ft_env_search_value(char **env, char *var);
void					ft_env_set_var(char ***env, char *var, char *v);
int						ft_env_replace_var(char ***env, char *var, char *n);
void					ft_env_add_var(char ***env, char *n);
int						ft_env_count_var(char **env);

// ENV / UTILS 2

int						get_shlvl_value(char **envp);
char					*get_env_value(char **env, const char *var);

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
t_ctx					ft_lexer_ctx_type(char c);

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

int						ft_token_sameword(t_character *a, t_character *b);
void					ft_token_add_word_token(t_token *tk, t_character *ch,
							size_t i);
int						ft_token_dollar(t_character *ch);
int						ft_token_dollar_exp(t_character *c);
int						ft_token_special_var(t_character *word_start);

//	TOKEN / UTILS 2

t_token					*ft_token_add(t_type t, size_t i);
void					ft_token_append(t_token **hd, t_token **tl,
							t_token *tk);
int						ft_isoperator_type(t_type type);
int						ft_isvalid_char(char c);
size_t					ft_token_wordlen(t_character *ch);

// UTILS / UTILS LIST

t_all					*ft_init_all(int i);
t_command				*ft_init_struct(t_token *t);
void					ft_free_token(t_token *hd);

// UTILS / FREE

int						ft_free_program(t_character *c, t_token *t,
							t_command *cmd, int i);
void					ft_free_env(t_shell *s);
void					ft_free_char(t_character *c);

// 3.Parser / add.c
int						add_cmd(t_command *cmd, char *str);
int						add_argument(t_command *cmd, t_type type,
							const char *str);
int						add_redir(t_token **token_list, t_command **current);
int						handle_pipe(t_token **token_list, t_command **current);
int						handle_cmd_or_arg(t_token **token_list,
							t_command **current);

// 3.Parser / cmd.c
int						save_all(t_command *cmd, t_token *token_list);
t_command				*create_new_command(void);
t_command				*init_struct_globale(t_token *token_list);

// 3.Parser / init.c
t_arg					*create_arg(t_type type, const char *str);
t_redir					*create_redir(t_type type, const char *target,
							t_type target_type);
t_element				*create_element_arg(t_type type, const char *str);
t_element				*create_element_redir(t_type type, const char *target,
							t_type target_type);
void					add_element_to_command(t_command *cmd,
							t_element *element);

// 3.Parser / parse_token.c
int						parse_token(t_token *token_list);

// 3.Parser / utils.c
t_element				*lst_last_node(t_element *head);
int						is_redir(t_type type);
int						is_operator(t_type type);
int						is_command(t_type_cmd type);
t_type_cmd				identify_builtin(const char *str);

// 0.env / signals.c
void					ft_signal_init(void);
void					ft_signal_handler(int i);
int						ft_signal_check(void);
void					ft_signal_reset(void);

// expander.c
void					expander(t_command **cmd_list, t_shell *shell);

// norme
int						apply_redir(t_ios *ios, t_redir *r, t_shell *sh);
int						is_var_start(int c);
int						is_var_continue(int c);
int						is_valid_ident(const char *s);
void					remove_env_var(char ***penv, const char *name);
size_t					count_args(t_element *e);
int						is_numeric_word(const char *s);
char					to_exit_u8(const char *s);
int						is_valid_ident_export(const char *s);
char					*dup_n(const char *s, size_t n);
char					*make_env_kv(const char *name, const char *value);
int						setenv_in_vec(char ***penv, const char *name,
							const char *value);
void					fill_argv(t_element *e, char **argv);
char					**build_export_argv(t_element *e);
int						print_all_exports(t_shell *sh);
int						process_export_args(char **argv, int idx, t_shell *sh);
int						setenv_in_vec_cd(char ***penv, const char *name,
							const char *value);
int						exit_status_from_errno(int e);
int						is_directory(const char *p);
void					print_exec_error(const char *path, const char *argv0,
							int e);
char					*join_path(const char *dir, const char *cmd);
char					*resolve_in_path(const char *cmd, char **env);
int						is_last_cmd(t_command *cmd);
int						is_simple_builtin_type(t_type_cmd c);
int						exec_with_path(char **argv, t_shell *sh);
void					print2_err(const char *a, const char *b);
void					putstr_err(const char *s);
size_t					count_args_nonempty(const t_command *cmd);
void					free_argv_dup(char **argv);
int						child_prepare_fds(t_command *cmd, int prev_rd,
							int out_wr, t_shell *sh);
pid_t					spawn_one(t_command *cmd, int prev_rd, int out_wr,
							t_shell *sh);
int						wait_all(pid_t *pids, int n);
int						run_single_builtin(t_command *cmd, t_shell *sh,
							t_all *all);
void					restore_stdio_and_close(int saved_in, int saved_out);
int						apply_redirs_for_single(t_command *cmd, int saved_in,
							int saved_out, t_shell *sh);
int						save_stdio(int *saved_in, int *saved_out);
void					advance_pipe_state(int *prev_rd, t_pipeinfo *pi);
void					cleanup_on_fail(int *prev_rd, t_pipeinfo *pi);

// exec
int						run_pipeline(t_all *all, t_command *cmd_list,
							t_shell *sh);
int						exec_builtin(t_command *cmd, t_shell *sh, t_all *all);

// redic
void					close_redirs(t_ios *ios);
int						apply_redirs(const t_ios *ios);
int						collect_redirs_fds(t_element *elem, t_ios *ios,
							t_shell *sh);
int						open_in(const char *path);
int						open_out_trunc(const char *path);
int						open_out_append(const char *path);

// heredoc
int						create_heredoc_fd(char *delim, t_shell *sh);

// builtin
int						builtin_echo(t_command *cmd, t_shell *sh);
int						builtin_pwd(t_command *cmd, t_shell *sh);
int						builtin_cd(t_command *cmd, t_shell *sh);
int						builtin_export(t_command *cmd, t_shell *sh);
int						builtin_unset(t_command *cmd, t_shell *sh);
int						builtin_env(t_command *cmd, t_shell *sh);
int						builtin_exit(t_command *cmd, t_shell *sh, t_all *all);

// Helper de détection
void					print_export_line(const char *entry);
void					print_export_error(const char *s);
int						handle_export_arg(const char *arg, t_shell *sh);
int						is_builtin_cmd(t_type_cmd cmd);

// 6.free/ free.c
t_all					*get_all(int reset);
void					free_env(t_shell *shell);
void					free_character_list(t_character *head);
void					free_token_list(t_token *head);

// 6.free/ free2.c
void					cleanup(t_command *cmd);
void					cleanall(t_character *char_list, t_token *token_list,
							t_command *cmd);

// free/ 6.error
void					ft_putstr_fd(char *s, int fd);
void					print_error(char *msg);
void					print_syntax_error(char *token);
int						exit_too_many_args(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/02 18:11:44 by corentindes      ###   ########.fr       */
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
	char			*var;
	char			*value;
	struct s_envp	*next;
}					t_envp;

//	STRUCTURE VAR

typedef struct s_var
{
	char			*var;
	struct s_envp	*next;
}					t_var;

t_var				g_vars_to_check[] = {{"PATH"}, {"PWD"}, {"SHLVL"}, {"HOME"},
					{"TERM"}, {"OLDPWD"}, {NULL}};

//	STRUCTURE TOKEN

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

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
	TOKEN_OR,
	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_EOF
}					t_token_type;

//	ENV / UTILS

void				ft_prompt(void);
t_envp				*ft_create_envp(char *str);
t_envp				*ft_init_envp(char **envp);
t_envp				*ft_search_var(t_envp *lst, char *var);
void				ft_free_envp(t_envp *lst);

//	ENV / VAR

int					check_error_var(t_envp **envp, char *var);
int					ft_check_var(t_envp **envp, char *var);
int					ft_change_var(t_envp **envp, t_envp *t, char *var);
int					shlvl(t_envp *t);

//	PARSER / PARSE

void				parse(char *line);


void				add_token(t_token **head, t_token *new_token);
t_token				*create_token(t_token_type type, const char *value);

void				parse_single_operator(char *line, int i);
void				parse_double_operator(char *line, int i);
int					ft_parse_word(char *line, int i);

#endif

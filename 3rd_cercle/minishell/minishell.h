/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/26 01:47:48 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }					t_list;

// typedef enum e_list_type
// {
// 	TOK_WORD,
// 	TOK_PIPE,
// 	TOK_REDIR_IN
// }					t_list_type;

// typedef struct s_token
// {
// 	t_list_type		type;
// 	char			*value;
// }					t_token;

// typedef struct s_cmd
// {
// 	char			**argv;
// 	char			*infile;
// 	char			*outfile;
// 	int				append;
// }					t_cmd;

void ft_prompt (void);

#endif

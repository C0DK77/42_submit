/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/16 18:25:44 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_syntax_error(t_token *n, t_token *prev)
{
	if ((n->type >= PIPE && n->type <= BACKGRD))
	{
		if (!prev && (n->type == PIPE || n->type == AND_IF || n->type == OR_IF
				|| n->type == SEMIC || n->type == AND))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(n->value, 2);
			ft_putstr_fd("'\n", 2);
			g_exit_status = 2;
			return (0);
		}
		if (!n->next || (n->next->type >= PIPE && n->next->type <= BACKGRD))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if (n->next)
				ft_putstr_fd(n->next->value, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			g_exit_status = 2;
			return (0);
		}
	}
	return (1);
}

int	ft_token_check(t_token *n)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = n;
	while (current)
	{
		if (!ft_check_syntax_error(current, prev))
			return (0);
		prev = current;
		current = current->next;
	}
	return (1);
}

// char	*ft_token_isquote(t_envp *l, char **w, char *s)
// {
// 	char	quote;
// 	char	*start;

// 	quote = *s;
// 	s++;
// 	start = s;
// 	while (*s && *s != quote)
// 		s++;
// 	if (quote == '"')
// 		ft_token_word_dbquote(l, w, start, s);
// 	else
// 		ft_token_word_sgquote(w, s, start);
// 	if (*s)
// 		s++;
// 	return (s);
// }

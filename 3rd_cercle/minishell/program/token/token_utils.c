/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 17:22:07 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_isquote(t_envp *l, char **w, char *s)
{
	char	quote;
	char	*start;

	quote = *s;
	s++;
	start = s;
	while (*s && *s != quote)
		s++;
	if (quote == '"')
		ft_token_word_dbquote(l, w, start, s);
	else
		ft_token_word_sgquote(w, s, start);
	if (*s)
		s++;
	return (s);
}

int	ft_token_check(t_token *n)
{
	t_token			*prev;
	t_token_type	t;

	prev = NULL;
	while (n)
	{
		t = n->type;
		if (!ft_token_check_bis(n, prev, 1) && (t == PIPE || t == AND_IF
				|| t == OR_IF || t == SEMIC || t == AND))
			return (0);
		if ((t == R_IN || t == R_OUT || t == R_APPEND || t == HERE)
			&& !ft_token_check_bis(n, prev, 2))
			return (0);
		if (!ft_token_check_bis(n, prev, 1) && (prev->type >= PIPE
				&& prev->type <= BACKGRD) && (t >= PIPE && t <= BACKGRD))
			return (0);
		prev = n;
		n = n->next;
	}
	return (1);
}

int	ft_token_check_bis(t_token *n, t_token *prev, int i)
{
	if (!prev && i == 1)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2),
			ft_putstr_fd(n->value, 2), ft_putstr_fd("'\n", 2), 0);
	if (!n->next && i == 2)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2),
			ft_putstr_fd("`newline'\n", 2), 1);
	if (n->next->type != WRD && i == 2)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2),
			ft_putstr_fd(n->value, 2), ft_putstr_fd("'\n", 2), 0);
	if (prev && i == 3)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2),
			ft_putstr_fd(n->value, 2), ft_putstr_fd("'\n", 2), 0);
	return (1);
}

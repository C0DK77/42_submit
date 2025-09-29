/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 10:06:35 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_token_isquote(t_envp *env, char **w, char *s)
{
	char	quote;
	char	*start;

	quote = *s;
	s++;
	start = s;
	while (*s && *s != quote)
		s++;
	if (quote == '"')
		ft_token_word_dbquote(env, w, start, s);
	else
		ft_token_word_sgquote(w, s, start);
	if (*s)
		s++;
	return (s);
}

int	ft_token_check(t_token *token)
{
	t_token			*p;
	t_token_type	type;

	p = NULL;
	while (token)
	{
		type = token->type;
		if ((type == PIPE || type == AND_IF || type == OR_IF || type == SEMIC
				|| type == AND) && !ft_token_check_bis(token, p, 1))
			return (0);
		if ((type == R_IN || type == R_OUT || type == R_APPEND || type == HERE)
			&& !ft_token_check_bis(token, p, 2))
			return (0);
		if (p && (p->type >= PIPE && p->type <= BACKGRD) && (type >= PIPE
				&& type <= BACKGRD) && !ft_token_check_bis(token, p, 3))
			return (0);
		p = token;
		token = token->next;
	}
	return (1);
}

int	ft_token_check_bis(t_token *token, t_token *p, int i)
{
	if (!p && i == 1)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell1: syntax error near unexpected token `", 2),
			ft_putstr_fd(token->value, 2), ft_putstr_fd("'\n", 2), 0);
	if (!token->next && i == 2)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell2: syntax error near unexpected token ", 2),
			ft_putstr_fd("`newline'\n", 2), 1);
	if (token->next->type != WRD && i == 2)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell2: syntax error near unexpected token `", 2),
			ft_putstr_fd(token->value, 2), ft_putstr_fd("'\n", 2), 0);
	if (p && i == 3)
		return (g_exit_status = 2,
			ft_putstr_fd("minishell3: syntax error near unexpected token `", 2),
			ft_putstr_fd(token->value, 2), ft_putstr_fd("'\n", 2), 0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:10:30 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/23 08:41:58 by corentindes      ###   ########.fr       */
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
		if ((t == R_IN || t == R_OUT || t == R_APPEND || t == HERE))
			if (!ft_token_check_rin_rout_rappend_here(n))
				return (0);
		if (t == PIPE || t == AND_IF || t == OR_IF || t == SEMIC || t == AND)
			if (!ft_token_check_rin_rout_rappend_here(n))
				return (0);
		if (prev && (prev->type >= PIPE && prev->type <= BACKGRD) && (t >= PIPE
				&& t <= BACKGRD))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			return (ft_putstr_fd(n->value, 2), ft_putstr_fd("'\n", 2), 0);
		}
		prev = n;
		n = n->next;
	}
	return (1);
}

int	ft_token_check_rin_rout_rappend_here(t_token *n)
{
	if (!n->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		return (ft_putstr_fd("`newline'\n", 2), 1);
	}
	if (n->next->type != WRD)
	{
		g_exit_status = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		return (ft_putstr_fd(n->value, 2), ft_putstr_fd("'\n", 2), 0);
	}
	return (1);
}

int	ft_token_check_pipe_andif_orif_semic_and(t_token *n, t_token *prev)
{
	if (!prev)
	{
		g_exit_status = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		return (ft_putstr_fd(n->value, 2), ft_putstr_fd("'\n", 2), 1);
	}
	if (!n->next || n->next->type != WRD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		return (ft_putstr_fd("`newline'\n", 2), 1);
	}
	return (0);
}

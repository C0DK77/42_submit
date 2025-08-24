/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/24 14:51:19 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_handle_redirection(t_parsing *n, t_token **t)
{
	t_token	*l;

	l = *t;
	if (!l->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `lline'\n",
			2);
		return (1);
	}
	if (l->next->type != WRD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		return (ft_putstr_fd(l->next->value, 2), ft_putstr_fd("'\n", 2), 1);
	}
	ft_redirection_type(n, l->type, l->next->value);
	*t = l->next;
	return (0);
}

void	ft_redirection_type(t_parsing *n, int t, char *f)
{
	if (t == R_IN)
	{
		n->infiles = ft_parse_add_value(n->infiles, f);
	}
	else if (t == R_OUT || t == R_APPEND)
	{
		n->outfiles = ft_parse_add_value(n->outfiles, f);
		n->append = ft_parse_add_append(n->append, (t == R_APPEND));
	}
	else if (t == HERE)
	{
		n->infiles = ft_parse_add_value(n->infiles, f);
		n->heredoc = 1;
	}
}

t_parsing	*ft_parse_line(t_token *t)
{
	t_parsing	*a;
	t_parsing	*n;
	t_parsing	*p;

	a = NULL;
	n = NULL;
	p = NULL;
	while (t)
	{
		if (!n && !ft_parse_add_node(&n, &p, &a))
			return (NULL);
		if (t->type == WRD && t->value)
			n->line = ft_parse_add_value(n->line, t->value);
		else if ((t->type == R_IN || t->type == R_OUT || t->type == R_APPEND
				|| t->type == HERE) && ft_handle_redirection(n, &t))
			return (NULL);
		ft_parse_type(n, t);
		if (t->type == PIPE || t->type == AND_IF || t->type == OR_IF
			|| t->type == AND || t->type == SEMIC)
			n = NULL;
		t = t->next;
	}
	return (a);
}

void	ft_parse_type(t_parsing *n, t_token *t)
{
	if (!n || !t)
		return ;
	if (t->type == PIPE)
		n->sep = SEP_PIPE;
	else if (t->type == AND_IF)
		n->sep = SEP_AND_IF;
	else if (t->type == OR_IF)
		n->sep = SEP_OR_IF;
	else if (t->type == AND)
		n->sep = SEP_BACKGROUND;
	else if (t->type == SEMIC)
		n->sep = SEP_SEQ;
}

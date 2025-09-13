/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/13 19:30:56 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_redirection(t_parsing *n, t_token **t)
{
	t_token	*l;

	l = *t;
	if (!l->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
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

// int	parse_step(t_parsing **a, t_parsing **n, t_parsing **p, t_token **t)
// {
// 	if (!*n && !ft_parse_add_node(a, n, p))
// 		return (0);
// 	if ((*t)->type == WRD && (*t)->value)
// 		(*n)->line = ft_parse_add_value((*n)->line, (*t)->value);
// 	else if (((*t)->type == R_IN || (*t)->type == R_OUT
// 			|| (*t)->type == R_APPEND || (*t)->type == HERE)
// 		&& ft_handle_redirection(*n, t))
// 		return (0);
// 	ft_parse_type(*n, *t);
// 	if ((*t)->type == PIPE || (*t)->type == AND_IF || (*t)->type == OR_IF
// 		|| (*t)->type == AND || (*t)->type == SEMIC)
// 		*n = NULL;
// 	*t = (*t)->next;
// 	return (1);
// }

// t_parsing	*ft_parse_line(t_token *t)
// {
// 	t_parsing	*a;
// 	t_parsing	*n;
// 	t_parsing	*p;

// 	a = NULL;
// 	n = NULL;
// 	p = NULL;
// 	while (t)
// 	{
// 		if (!parse_step(&a, &n, &p, &t))
// 			return (NULL);
// 	}
// 	return (a);
// }

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

void	ft_redirection_type(t_parsing *n, int t, char *f)
{
	if (t == R_IN)
		n->redirs = ft_redir_add(n->redirs, REDIR_IN, f);
	else if (t == R_OUT)
		n->redirs = ft_redir_add(n->redirs, REDIR_OUT, f);
	else if (t == R_APPEND)
		n->redirs = ft_redir_add(n->redirs, REDIR_APPEND, f);
	else if (t == HERE)
		n->redirs = ft_redir_add(n->redirs, REDIR_HEREDOC, f);
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

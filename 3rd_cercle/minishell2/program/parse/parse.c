/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 00:48:37 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

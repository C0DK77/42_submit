/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:14 by codk              #+#    #+#             */
/*   Updated: 2025/10/08 19:24:52 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lexer_empty_str(t_ctx ctx, char next_c, char next_next_c)
{
	t_ctx	next_ctx;

	next_ctx = ft_lexer_get_type(next_c);
	if (ctx == next_ctx && (ft_isoperator(next_next_c)
			|| ft_isspace(next_next_c) || next_next_c == '\0'))
		return (1);
	return (0);
}

int	ft_lexer_append(t_character **head, t_character **tail, char c, t_ctx ctx)
{
	t_character	*n;

	n = ft_lexer_new_node(c, ctx, *tail);
	if (!n)
		return (ft_free_character(*head), 0);
	if (!*head)
		*head = n;
	*tail = n;
	return (1);
}

t_character	*ft_lexer_new_node(char c, t_ctx ctx, t_character *tail)
{
	t_character	*n;

	n = malloc(sizeof(t_character));
	if (!n)
		return (NULL);
	n->c = c;
	n->word_id = 0;
	if (ctx == S_QUOTE)
		n->type = LITERAL;
	else if (ctx == D_QUOTE)
	{
		if (c == '$')
			n->type = DOLLAR;
		else
			n->type = LITERAL;
	}
	else
		n->type = ft_lexer_get_type(c);
	n->context = ctx;
	n->next = NULL;
	n->prev = tail;
	if (tail)
		tail->next = n;
	return (n);
}

void	ft_free_character(t_character *c)
{
	t_character	*t;

	while (c)
	{
		t = c->next;
		free(c);
		c = t;
	}
}

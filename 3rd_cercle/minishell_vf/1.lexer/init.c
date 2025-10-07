/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:14 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 16:25:49 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_character	*init_node(char c, t_ctx ctx, t_character *tail)
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
		n->type = get_character_type(c);
	n->context = ctx;
	n->next = NULL;
	n->prev = tail;
	if (tail)
		tail->next = n;
	return (n);
}

int	check_empty_string(t_ctx ctx, char next_c, char next_next_c)
{
	t_ctx	next_ctx;

	next_ctx = get_ctx_type(next_c);
	if (ctx == next_ctx && (is_operator_char(next_next_c)
			|| ft_isspace(next_next_c) || next_next_c == '\0'))
		return (1);
	return (0);
}

int	check_oprhan_quote(t_character *head, t_ctx ctx)
{
	if (ctx != NONE)
		return (print_error("Find an orphan quote"), free_character_list(head),
			1);
	return (0);
}

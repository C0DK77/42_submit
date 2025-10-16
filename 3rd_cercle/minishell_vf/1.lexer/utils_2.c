/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:28 by codk              #+#    #+#             */
/*   Updated: 2025/10/15 20:44:47 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ctx	get_ctx_type(char c)
{
	if (c == 34)
		return (D_QUOTE);
	else if (c == 39)
		return (S_QUOTE);
	return (NONE);
}

// ???????????????????????????????

int	process_space(char *line, int *i, t_ctx ctx, t_build_state *st)
{
	if (ctx == NONE && ft_isspace(line[*i]))
	{
		if (st->tail && st->tail->word_id == st->word)
			st->word++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	process_token(char *s, int *i, t_ctx ctx, t_build_state *b)
{
	if (ctx == NONE && ft_isoperator(s[*i]))
	{
		if (b->tail && b->tail->word_id == b->word
			&& !ft_isoperator(b->tail->c))
			b->word++;
		else if (b->tail && b->tail->word_id == b->word
			&& ft_isoperator(b->tail->c) && b->tail->c != s[*i])
			b->word++;
		if (!ft_lexer_append(&b->head, &b->tail, s[*i], ctx))
			return (0);
		b->tail->word_id = b->word;
	}
	else
	{
		if (b->tail && b->tail->word_id == b->word && b->tail->context == NONE
			&& ft_isoperator(b->tail->c))
			b->word++;
		if (!ft_lexer_append(&b->head, &b->tail, s[*i], ctx))
			return (0);
		b->tail->word_id = b->word;
	}
	(*i)++;
	return (1);
}

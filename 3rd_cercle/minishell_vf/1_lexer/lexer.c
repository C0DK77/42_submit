/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:08 by codk              #+#    #+#             */
/*   Updated: 2025/10/26 07:48:41 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_character	*ft_lexer_init(char *l)
{
	int				i;
	t_ctx			ctx;
	t_build_state	b;

	if (!l)
		return (NULL);
	ctx = NONE;
	b.head = NULL;
	b.tail = NULL;
	b.word = 0;
	i = 0;
	while (l[i])
	{
		if (ft_lexer_parse_quote(l, &i, &ctx, &b))
			continue ;
		if (ft_lexer_parse_space(l, &i, ctx, &b))
			continue ;
		if (!ft_lexer_parse_token(l, &i, ctx, &b))
			return (NULL);
	}
	if (ctx != NONE)
		return (ft_putstr_fd("minishell: Find orphan quote\n", 2),
			ft_free_char(b.head), NULL);
	return (b.head);
}

int	ft_lexer_parse_quote(char *l, int *i, t_ctx *ctx, t_build_state *b)
{
	if (ft_lexer_parse_context(l[*i], ctx))
	{
		if (*ctx != NONE && l[*i + 1] != '\0')
		{
			if (ft_lexer_empty_str(*ctx, l[*i + 1], l[*i + 2]))
			{
				if (!ft_lexer_append(&b->head, &b->tail, '\0', *ctx))
					return (0);
				b->tail->word_id = b->word;
				*i += 2;
				*ctx = NONE;
				return (1);
			}
		}
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_lexer_parse_space(char *l, int *i, t_ctx ctx, t_build_state *b)
{
	if (ctx == NONE && ft_isspace(l[*i]))
	{
		if (b->tail && b->tail->word_id == b->word)
			b->word++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_lexer_parse_token(char *s, int *i, t_ctx ctx, t_build_state *b)
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

int	ft_lexer_parse_context(char c, t_ctx *ctx)
{
	if ((c == 34 || c == 39) && (*ctx == NONE))
	{
		if (c == 34)
			*ctx = D_QUOTE;
		else if (c == 39)
			*ctx = S_QUOTE;
		return (1);
	}
	else if ((c == 34 || c == 39) && (*ctx != NONE))
	{
		if (c == 34 && *ctx == D_QUOTE)
		{
			*ctx = NONE;
			return (1);
		}
		else if (c == 39 && *ctx == S_QUOTE)
		{
			*ctx = NONE;
			return (1);
		}
	}
	return (0);
}

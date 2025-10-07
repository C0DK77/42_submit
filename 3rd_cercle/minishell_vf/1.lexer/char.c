/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:08 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 16:23:29 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_character	*ft_lexer_init_list(char *l)
{
	t_ctx			ctx;
	t_build_state	st;
	int				i;

	if (!l)
		return (NULL);
	ctx = NONE;
	st.head = NULL;
	st.tail = NULL;
	st.word = 0;
	i = 0;
	while (l[i])
	{
		if (process_quote(l, &i, &ctx, &st))
			continue ;
		if (process_space(l, &i, ctx, &st))
			continue ;
		if (!process_token(l, &i, ctx, &st))
			return (NULL);
	}
	if (check_oprhan_quote(st.head, ctx))
		return (NULL);
	return (st.head);
}

int	process_quote(char *line, int *i, t_ctx *ctx, t_build_state *st)
{
	if (handle_quote_context(line[*i], ctx))
	{
		if (*ctx != NONE && line[*i + 1] != '\0')
		{
			if (check_empty_string(*ctx, line[*i + 1], line[*i + 2]))
			{
				if (!append_char(&st->head, &st->tail, '\0', *ctx))
					return (0);
				st->tail->word_id = st->word;
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

int	append_char(t_character **head, t_character **tail, char ch, t_ctx ctx)
{
	t_character	*new;

	new = init_node(ch, ctx, *tail);
	if (!new)
		return (free_character_list(*head), 0);
	if (!*head)
		*head = new;
	*tail = new;
	return (1);
}

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

static int	process_token(char *line, int *i, t_ctx ctx, t_build_state *st)
{
	if (ctx == NONE && is_operator_char(line[*i]))
	{
		if (st->tail && st->tail->word_id == st->word
			&& !is_operator_char(st->tail->c))
			st->word++;
		else if (st->tail && st->tail->word_id == st->word
			&& is_operator_char(st->tail->c) && st->tail->c != line[*i])
			st->word++;
		if (!append_char(&st->head, &st->tail, line[*i], ctx))
			return (0);
		st->tail->word_id = st->word;
	}
	else
	{
		if (st->tail && st->tail->word_id == st->word
			&& st->tail->context == NONE && is_operator_char(st->tail->c))
			st->word++;
		if (!append_char(&st->head, &st->tail, line[*i], ctx))
			return (0);
		st->tail->word_id = st->word;
	}
	(*i)++;
	return (1);
}

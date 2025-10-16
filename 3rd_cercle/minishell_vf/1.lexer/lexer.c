/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:08 by codk              #+#    #+#             */
/*   Updated: 2025/10/08 19:28:34 by corentindes      ###   ########.fr       */
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
		if (ft_lexer_parse_quote(l, &i, ctx, &b))
			continue ;
		if (!ft_lexer_parse_quote(l, &i, ctx, &b))
			return (NULL);
	}
	if (ft_lexer_isempty_quote(b.head, ctx))
		return (NULL);
	return (b.head);
}

int	ft_lexer_parse_quote(char *line, int *i, t_ctx *ctx, t_build_state *b)
{
	if (ft_lexer_parse_context(line[*i], ctx))
	{
		if (*ctx != NONE && line[*i + 1] != '\0')
		{
			if (ft_lexer_empty_str(*ctx, line[*i + 1], line[*i + 2]))
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

int	ft_lexer_parse_context(char c, t_ctx *ctx)
{
	if ((c == 34 || c == 39) && (*ctx == NONE))
	{
		*ctx = ft_lexer_get_type(c);
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

t_type	ft_lexer_get_type(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '.' || c == '/' || c == '_' || c == '*'
		|| c == '[' || c == ']' || c == ',' || c == ':' || c == '+' || c == '='
		|| c == '%' || c == '#' || c == '@' || c == '-' || c == '?' || c == '!'
		|| c == '&')
		return (LITERAL);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIR_IN);
	else if (c == '>')
		return (REDIR_OUT);
	else if (c == '$')
		return (DOLLAR);
	return (UNKNOWN);
}

int	ft_lexer_isempty_quote(t_character *head, t_ctx ctx)
{
	if (ctx != NONE)
		return (print_error("Find an orphan quote"), ft_free_character(head),
			1);
	return (0);
}

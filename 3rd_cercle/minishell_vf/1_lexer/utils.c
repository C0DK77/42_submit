/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:14 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 17:51:43 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	ft_lexer_char_type(char c)
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

int	ft_lexer_empty_str(t_ctx ctx, char a, char b)
{
	t_ctx	t;

	t = ft_lexer_ctx_type(a);
	if (ctx == t && (ft_isoperator(b) || ft_isspace(b) || b == '\0'))
		return (1);
	return (0);
}

int	ft_lexer_append(t_character **hd, t_character **tl, char a, t_ctx ctx)
{
	t_character	*t;

	t = ft_lexer_new_node(a, ctx, *tl);
	if (!t)
		return (ft_free_char(*hd), 0);
	if (!*hd)
		*hd = t;
	*tl = t;
	return (1);
}

t_character	*ft_lexer_new_node(char a, t_ctx ctx, t_character *tl)
{
	t_character	*t;

	t = malloc(sizeof(t_character));
	if (!t)
		return (NULL);
	t->c = a;
	t->word_id = 0;
	if (ctx == S_QUOTE)
		t->type = LITERAL;
	else if (ctx == D_QUOTE)
	{
		if (a == '$')
			t->type = DOLLAR;
		else
			t->type = LITERAL;
	}
	else
		t->type = ft_lexer_char_type(a);
	t->context = ctx;
	t->next = NULL;
	t->prev = tl;
	if (tl)
		tl->next = t;
	return (t);
}

t_ctx	ft_lexer_ctx_type(char c)
{
	if (c == 34)
		return (D_QUOTE);
	else if (c == 39)
		return (S_QUOTE);
	return (NONE);
}

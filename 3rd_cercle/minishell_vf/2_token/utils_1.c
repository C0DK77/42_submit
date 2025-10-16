/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:41 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 19:09:00 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token_sameword(t_character *a, t_character *b)
{
	if (a->word_id != b->word_id)
		return (0);
	return (1);
}

void	ft_token_add_word_token(t_token *tk, t_character *ch, size_t i)
{
	t_character	*t;
	size_t		i;

	t = ch;
	i = 0;
	while (t && ft_token_sameword(ch, t) && !ft_token_isoperator(t->type))
	{
		tk->str[i] = t->c;
		i++;
		t = t->next;
	}
	tk->str[i] = '\0';
}

int	ft_token_dollar(t_character *ch)
{
	t_character	*t;
	t_character	*next;

	t = ch;
	while (t && ft_token_sameword(ch, t))
	{
		if (ft_token_dollar_exp(t))
		{
			next = t->next;
			if (next && next->c != '?')
				return (1);
		}
		t = t->next;
	}
	return (0);
}

int	ft_token_dollar_exp(t_character *c)
{
	t_character	*next;

	if (!c || c->c != '$')
		return (0);
	if (c->context == S_QUOTE)
		return (0);
	next = c->next;
	if (!next || !ft_token_sameword(c, next))
		return (0);
	if (c->context != next->context)
		return (0);
	if (next->c == '?' || ft_isvalid_char(next->c))
		return (1);
	return (0);
}

int	ft_token_special_var(t_character *ch)
{
	t_character	*t;
	t_character	*next;

	t = ch;
	while (t && ft_token_sameword(ch, t))
	{
		if (t->c == '$' && t->context != S_QUOTE)
		{
			next = t->next;
			if (next && ft_token_sameword(t, next)
				&& t->context == next->context && next->c == '?')
				return (1);
		}
		t = t->next;
	}
	return (0);
}

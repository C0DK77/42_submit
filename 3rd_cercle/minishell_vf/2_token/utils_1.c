/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:41 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 10:51:19 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_add_word_token(t_token *tk, t_character *ch, size_t i)
{
	t_character	*t;
	size_t		i;

	t = ch;
	i = 0;
	while (t && ch->word_id == t->word_id && !ft_token_isoperator_type(t->type))
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
	while (t && ch->word_id == t->word_id)
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
	if (!next || c->word_id != next->word_id)
		return (0);
	if (c->context != next->context)
		return (0);
	if (next->c == '?' || ft_isalpha(next->c) || next->c == '_')
		return (1);
	return (0);
}

int	ft_token_special_var(t_character *ch)
{
	t_character	*t;
	t_character	*next;

	t = ch;
	while (t && ch->word_id == t->word_id)
	{
		if (t->c == '$' && t->context != S_QUOTE)
		{
			next = t->next;
			if (next && t->word_id == next->word_id
				&& t->context == next->context && next->c == '?')
				return (1);
		}
		t = t->next;
	}
	return (0);
}

int	ft_token_isoperator_type(t_type type)
{
	if (type == PIPE || type == APPEND || type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT)
		return (1);
	return (0);
}

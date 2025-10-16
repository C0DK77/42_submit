/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:41 by codk              #+#    #+#             */
/*   Updated: 2025/10/15 20:47:05 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	detect_operator_type(t_character *c, t_character *n, t_type *t,
		size_t *l)
{
	*t = UNKNOWN;
	*l = 1;
	if (c->c == '|')
		*t = PIPE;
	else if (c->c == '<')
	{
		if (n && ft_is_samewrd(c, n) && n->c == '<')
		{
			*t = HEREDOC;
			*l = 2;
		}
		else
			*t = REDIR_IN;
	}
	else if (c->c == '>')
	{
		if (n && ft_is_samewrd(c, n) && n->c == '>')
		{
			*t = APPEND;
			*l = 2;
		}
		else
			*t = REDIR_OUT;
	}
}

int	is_expandable_dollar(t_character *c)
{
	t_character	*next;

	if (!c || c->c != '$')
		return (0);
	if (c->context == S_QUOTE)
		return (0);
	next = c->next;
	if (!next || !ft_is_samewrd(c, next))
		return (0);
	if (c->context != next->context)
		return (0);
	if (next->c == '?' || valid_variable_char(next->c))
		return (1);
	return (0);
}

int	word_has_special_variable(t_character *word_start)
{
	t_character	*current;
	t_character	*next;

	current = word_start;
	while (current && ft_is_samewrd(word_start, current))
	{
		if (current->c == '$' && current->context != S_QUOTE)
		{
			next = current->next;
			if (next && ft_is_samewrd(current, next)
				&& current->context == next->context && next->c == '?')
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	word_has_expandable_dollar(t_character *word_start)
{
	t_character	*current;
	t_character	*next;

	current = word_start;
	while (current && ft_is_samewrd(word_start, current))
	{
		if (is_expandable_dollar(current))
		{
			next = current->next;
			if (next && next->c != '?')
				return (1);
		}
		current = current->next;
	}
	return (0);
}

size_t	ft_wordlen(t_character *start)
{
	t_character	*cur;
	size_t		len;

	cur = start;
	len = 0;
	while (cur && ft_is_samewrd(start, cur) && !ft_isoperator_type(cur->type))
	{
		len++;
		cur = cur->next;
	}
	return (len);
}

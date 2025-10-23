/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:33:47 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 07:20:12 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_init(t_character *c)
{
	t_token	*hd;
	t_token	*tl;

	hd = NULL;
	tl = NULL;
	while (c)
	{
		if (ft_isoperator_type(c->type) && !ft_token_add_operator(&hd, &tl, &c))
			return (ft_free_token(hd), NULL);
		else if (!ft_token_add_word(&hd, &tl, &c))
			return (ft_free_token(hd), NULL);
	}
	return (hd);
}

int	ft_token_add_operator(t_token **hd, t_token **tl, t_character **ch)
{
	t_character	*c;
	t_character	*n;
	t_type		type;
	size_t		i;
	t_token		*tk;

	c = *ch;
	if (!c)
		return (0);
	n = c->next;
	ft_token_operator(c, n, &type, &i);
	tk = ft_token_add(type, i);
	if (!tk)
		return (0);
	tk->str[0] = c->c;
	if (i == 2 && n)
		tk->str[1] = n->c;
	tk->str[i] = '\0';
	ft_token_append(hd, tl, tk);
	if (i == 2 && n)
		*ch = n->next;
	else
		*ch = c->next;
	return (1);
}

int	ft_token_add_word(t_token **hd, t_token **tl, t_character **ch)
{
	t_character	*l;
	t_character	*t;
	size_t		i;
	t_type		type;
	t_token		*tk;

	l = *ch;
	i = ft_token_wordlen(l);
	if (i == 0 && ft_token_noword(hd, tl, ch, l))
		return (1);
	type = LITERAL;
	if (ft_token_special_var(l))
		type = SPECIAL_VARIABLE;
	else if (ft_token_dollar(l))
		type = DOLLAR;
	tk = ft_token_add(type, i);
	if (!tk)
		return (0);
	ft_token_add_word_token(tk, l, i);
	ft_token_append(hd, tl, tk);
	t = l;
	while (t && ft_token_sameword(l, t) && !ft_isoperator_type(t->type))
		t = t->next;
	*ch = t;
	return (1);
}

void	ft_token_operator(t_character *c, t_character *n, t_type *t, size_t *i)
{
	*t = UNKNOWN;
	*i = 1;
	if (c->c == '|')
		*t = PIPE;
	else if (c->c == '<')
	{
		if (n && ft_token_sameword(c, n) && n->c == '<')
		{
			*t = HEREDOC;
			*i = 2;
		}
		else
			*t = REDIR_IN;
	}
	else if (c->c == '>')
	{
		if (n && ft_token_sameword(c, n) && n->c == '>')
		{
			*t = APPEND;
			*i = 2;
		}
		else
			*t = REDIR_OUT;
	}
}

int	ft_token_noword(t_token **hd, t_token **tl, t_character **ch,
		t_character *t)
{
	t_token	*tk;

	if (!t || !t->next)
		return (0);
	if (!t->word_id || !t->next->word_id)
		return (0);
	tk = ft_token_add(LITERAL, 0);
	if (!tk)
		return (0);
	ft_token_append(hd, tl, tk);
	*ch = (*ch)->next;
	return (1);
}

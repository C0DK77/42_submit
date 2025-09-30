/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:53:32 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/30 19:01:42 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_operator	*ft_token_ope_init_table(void)
{
	static t_operator	tb[9];

	tb[0].s = ">>";
	tb[0].type = R_APPEND;
	tb[1].s = ">";
	tb[1].type = R_OUT;
	tb[2].s = "<<";
	tb[2].type = HERE;
	tb[3].s = "<";
	tb[3].type = R_IN;
	tb[4].s = "||";
	tb[4].type = OR_IF;
	tb[5].s = "|";
	tb[5].type = PIPE;
	tb[6].s = "&&";
	tb[6].type = AND_IF;
	tb[7].s = "&";
	tb[7].type = AND;
	tb[8].s = NULL;
	tb[8].type = 0;
	return (tb);
}

t_token	*ft_token(t_envp *env, char *s)
{
	t_token	*token;

	token = NULL;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (!(*s))
			break ;
		else if (ft_isoperator(*s))
			s = ft_token_ope(&token, s);
		else
			s = ft_token_word(env, &token, s);
	}
	return (token);
}

t_token	*ft_token_init(t_token_type type, char *v, int i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = NULL;
	token->quoted = i;
	if (v)
	{
		token->value = ft_strdup(v);
		if (!token->value)
			return (free(token), NULL);
	}
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	ft_token_add(t_token **token, t_token *n)
{
	t_token	*t;

	if (!*token)
		*token = n;
	else
	{
		t = *token;
		while (t->next)
			t = t->next;
		t->next = n;
		n->prev = t;
	}
}

void	ft_token_free(t_token *token)
{
	t_token	*t;

	while (token)
	{
		t = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = t;
	}
}

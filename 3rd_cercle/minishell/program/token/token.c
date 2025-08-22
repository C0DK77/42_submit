/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:53:32 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 15:41:08 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_operator	*ft_token_operator_init_table(void)
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

t_token	*ft_token(char *s, t_envp *l)
{
	t_token	*t;

	t = NULL;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (!(*s))
			break ;
		else if (ft_isoperator(*s))
			s = ft_token_operator(&t, s);
		else
			s = ft_token_word(&t, s, l);
	}
	return (t);
}

t_token	*ft_token_init(t_token_type t, char *v)
{
	t_token	*n;

	n = malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	n->type = t;
	n->value = ft_strdup(v);
	n->next = NULL;
	return (n);
}

void	ft_token_add(t_token **l, t_token *n)
{
	t_token	*t;

	if (!*l)
		*l = n;
	else
	{
		t = *l;
		while (t->next)
			t = t->next;
		t->next = n;
	}
}

void	ft_token_free(t_token *l)
{
	t_token	*t;

	while (l)
	{
		t = l->next;
		if (l->value)
			free(l->value);
		free(l);
		l = t;
	}
}

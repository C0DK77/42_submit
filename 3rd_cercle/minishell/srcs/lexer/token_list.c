/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:34:17 by ecid              #+#    #+#             */
/*   Updated: 2025/09/27 15:47:22 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_init(t_token_type t, char *v)
{
	t_token	*n;

	n = malloc(sizeof(t_token));
	if (!n)
		return (NULL);
	n->type = t;
	n->value = NULL;
	if (v)
	{
		n->value = ft_strdup(v);
		if (!n->value)
		{
			free(n);
			return (NULL);
		}
	}
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

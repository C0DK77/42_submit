/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:03:58 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 16:04:37 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_history_add(t_history **h, const char *s)
{
	t_history	*n;
	t_history	*t;

	n = malloc(sizeof(t_history));
	if (!n)
		return ;
	n->line = strdup(s);
	n->next = NULL;
	if (!*h)
		*h = n;
	else
	{
		t = *h;
		while (t->next)
			t = t->next;
		t->next = n;
	}
}

void	ft_history_print(t_history *h)
{
	int	i;

	i = 1;
	while (h)
	{
		printf("%5d  %s\n", i, h->line);
		h = h->next;
		i++;
	}
}

void	ft_history_clear(t_history **h)
{
	t_history	*t;

	while (*h)
	{
		t = (*h)->next;
		free((*h)->line);
		free(*h);
		*h = t;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:25:51 by ecid              #+#    #+#             */
/*   Updated: 2025/08/17 16:26:11 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **s, t_envp **l)
{
	int		i;
	t_envp	*t;
	t_envp	*p;

	i = 1;
	while (s[i])
	{
		t = *l;
		p = NULL;
		while (t)
		{
			if (strcmp(t->var, s[i]) == 0)
			{
				if (p)
					p->next = t->next;
				else
					*l = t->next;
				free(t->var);
				if (t->value)
					free(t->value);
				free(t);
				break ;
			}
			p = t;
			t = t->next;
		}
		i++;
	}
	return (0);
}

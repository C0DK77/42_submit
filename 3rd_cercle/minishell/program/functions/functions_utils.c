/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:51:22 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/23 09:57:19 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_pwd_export_env_set(t_envp **l, char *s, char *v, int i)
{
	t_envp	*t;
	t_envp	*n;

	t = *l;
	while (t)
	{
		if (ft_strcmp(t->var, s) == 0)
		{
			if (v)
			{
				free(t->value);
				t->value = ft_strdup(v);
			}
			if (i)
				t->export = 1;
			return ;
		}
		t = t->next;
	}
	n = malloc(sizeof(t_envp));
	n->var = ft_strdup(s);
	if (v)
		n->value = ft_strdup(v);
	else
		NULL;
	n->export = i;
	n->next = (*l)->next;
	(*l)->next = n;
}

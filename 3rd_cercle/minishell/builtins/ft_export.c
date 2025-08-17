/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:20:41 by ecid              #+#    #+#             */
/*   Updated: 2025/08/17 15:20:55 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **s, t_envp **l)
{
	int		i;
	t_envp	*t;
	char	*eq;
	int		len;
	char	*name;
	char	*v;

	i = 1;
	if (!s[1])
	{
		t = *l;
		while (t)
		{
			if (t->export)
			{
				if (t->value)
					printf("declare -x %s=\"%s\"\n", t->var, t->value);
				else
					printf("declare -x %s\n", t->var);
			}
			t = t->next;
		}
		return (0);
	}
	while (s[i])
	{
		eq = ft_strchr(s[i], '=');
		if (eq)
		{
			len = eq - s[i];
			name = ft_strndup(s[i], len);
			v = ft_strdup(eq + 1);
			ft_env_set(l, name, v, 1);
			free(name);
			free(v);
		}
		else
			ft_env_set(l, s[i], NULL, 1);
		i++;
	}
	return (0);
}

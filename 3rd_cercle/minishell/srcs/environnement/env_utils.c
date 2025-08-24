/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/24 16:59:59 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_search_value(t_envp *l, char *v)
{
	while (l)
	{
		if (ft_strcmp(l->var, v) == 0)
			return (l->value);
		l = l->next;
	}
	return (NULL);
}

t_envp	*ft_env_search_node(t_envp *l, char *v)
{
	while (l)
	{
		if (ft_strcmp(l->var, v) == 0)
			return (l);
		l = l->next;
	}
	return (NULL);
}

void	ft_free_all(int argc, ...)
{
	int		i;
	va_list	argv;
	char	*s;

	i = 0;
	va_start(argv, argc);
	while (i < argc)
	{
		s = va_arg(argv, void *);
		if (s)
			free(s);
		i++;
	}
	va_end(argv);
}

void	ft_env_free(t_envp *l)
{
	t_envp	*t;

	while (l)
	{
		t = l->next;
		ft_free_all(2, l->var, l->value, l);
		l = t;
	}
}
int	ft_env_add_value(t_envp **l, char *s, char *v, int i)
{
	t_envp	*t;

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
				t->export = 0;
			return (0);
		}
		t = t->next;
	}
	return (1);
}

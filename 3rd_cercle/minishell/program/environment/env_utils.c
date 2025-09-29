/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:07 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 10:14:59 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*ft_env_search_value(t_envp *env, char *v)
{
	while (env)
	{
		if (ft_strcmp(env->var, v) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_envp	*ft_env_search_node(t_envp *env, char *v)
{
	while (env)
	{
		if (ft_strcmp(env->var, v) == 0)
			return (env);
		env = env->next;
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

void	ft_env_free(t_envp *env)
{
	t_envp	*t;

	while (env)
	{
		t = env->next;
		ft_free_all(2, env->var, env->value, env);
		env = t;
	}
}

int	ft_env_add_value(t_envp **env, char *s, char *v, int i)
{
	t_envp	*t;

	t = *env;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:51:45 by ecid              #+#    #+#             */
/*   Updated: 2025/09/28 22:18:24 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_export_count(t_envp *l)
{
	int	c;

	c = 0;
	while (l)
	{
		if (l->export)
			c++;
		l = l->next;
	}
	return (c);
}

static char	*env_join_kv(const char *k, const char *v)
{
	char	*entry;
	char	*res;

	entry = ft_strjoin((char *)k, "=");
	if (!entry)
		return (NULL);
	if (v)
		res = ft_strjoin(entry, (char *)v);
	else
		res = ft_strjoin(entry, "");
	free(entry);
	return (res);
}

static char	**env_cleanup_ret(char **env, int i)
{
	while (i > 0)
	{
		i--;
		free(env[i]);
	}
	free(env);
	return (NULL);
}

/* ≤ 25 lignes */
char	**ft_exec_env_array(t_envp *l)
{
	char	**env;
	int		i;
	t_envp	*t;

	env = malloc(sizeof(char *) * (env_export_count(l) + 1));
	if (!env)
		return (NULL);
	t = l;
	i = 0;
	while (t)
	{
		if (t->export)
		{
			env[i] = env_join_kv(t->var, t->value);
			if (!env[i])
				return (env_cleanup_ret(env, i));
			i++;
		}
		t = t->next;
	}
	env[i] = NULL;
	return (env);
}

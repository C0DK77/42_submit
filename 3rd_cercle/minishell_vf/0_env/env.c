/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:24 by codk              #+#    #+#             */
/*   Updated: 2025/12/02 17:29:53 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_set(char **env, t_shell *s)
{
	if (!env || !*env)
		s->env = ft_env_init();
	else
		s->env = ft_env_copy(env);
	if (!s->env)
		return (0);
	return (ft_env_init_shlvl(s, ft_env_search_value(env, "SHLVL")),
		s->last_exit = 0, 1);
}

char	**ft_env_init(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("USER=cdesjars");
	env[1] = ft_strdup("HOME=/home/cdesjars");
	env[2] = ft_strdup("PATH=/usr/bin:/bin");
	env[3] = ft_strdup("PWD=/home/cdesjars");
	env[4] = NULL;
	return (ft_env_check(env, 4));
}

char	**ft_env_copy(char **env)
{
	int		i;
	char	**n;

	i = 0;
	while (env && env[i])
		i++;
	n = malloc(sizeof(char *) * (i + 1));
	if (!n)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		n[i] = ft_strdup(env[i]);
		i++;
	}
	n[i] = NULL;
	return (ft_env_check(n, i));
}

char	**ft_env_check(char **env, int l)
{
	int	i;
	int	a;

	if (!env)
		return (NULL);
	a = 0;
	i = 0;
	while (i < l)
	{
		if (!env[i])
			a = 1;
		i++;
	}
	if (!a)
		return (env);
	i = 0;
	while (i < l)
	{
		free(env[i]);
		i++;
	}
	return (free(env), NULL);
}

void	ft_env_init_shlvl(t_shell *s, char *o)
{
	int		v;
	char	*n;

	if (!o || !*o)
		v = 1;
	else
	{
		v = ft_atoi(o);
		if (v < 0)
			v = 0;
		else if (v > 1000)
			v = 1;
		else
			v += 1;
	}
	s->shlvl = v;
	n = ft_itoa(v);
	if (n)
	{
		ft_env_set_var(&s->env, "SHLVL", n);
		free(n);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:24 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 11:17:30 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_set_env(char **env, t_shell *s)
{
	if (!env || !*env)
		s->env = ft_env_init_env();
	else
		s->env = ft_env_copy_env(env);
	if (!s->env)
		return (0);
	return (ft_env_init_shlvl(s, env), s->last_exit = 0, 1);
}

char	**ft_env_init_env(void)
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

char	**ft_env_copy_env(char **env)
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
	i = -1;
	while (i++ < l)
		if (!env[i])
			a = 1;
	if (!a)
		return (env);
	i = -1;
	while (i++ < l)
		if (env[i])
			free(env[i]);
	return (free(env), NULL);
}

void	ft_env_init_shlvl(t_shell *s, char **env)
{
	int		v;
	char	*n;

	v = 1;
	if (ft_env_search_value(env, "SHLVL"))
		v = ft_atoi(ft_env_search_value(env, "SHLVL") + 1);
	s->shlvl = v;
	n = ft_itoa(v);
	if (n)
	{
		ft_env_set_var(&s->env, "SHLVL", n);
		free(n);
	}
}

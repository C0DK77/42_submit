/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:32:38 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 11:17:12 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_env_search_value(char **env, char *var)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(var);
	if (!env || !var)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, l) == 0 && env[i][l] == '=')
			return (&env[i][l + 1]);
		i++;
	}
	return (NULL);
}

void	ft_env_set_var(char ***env, char *var, char *v)
{
	char	*n;
	char	*t;

	if (!env || !var || !v)
		return ;
	t = ft_strjoin(var, "=");
	if (!t)
		return (NULL);
	n = ft_strjoin(t, v);
	free(t);
	n = create_env_string(var, v);
	if (!n)
		return ;
	if (ft_env_replace_var(env, var, n))
		return ;
	ft_env_add_var(env, n);
}

int	ft_env_replace_var(char ***env, char *var, char *n)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(var);
	if (!*env)
		return (0);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, l) == 0 && (*env)[i][l] == '=')
		{
			free((*env)[i]);
			(*env)[i] = n;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_env_add_var(char ***env, char *n)
{
	char	**t;
	int		i;
	int		j;

	j = ft_env_count_var(*env);
	t = malloc(sizeof(char *) * (j + 2));
	if (!t)
		return (free(n));
	i = 0;
	while (i < j)
	{
		t[i] = (*env)[i];
		i++;
	}
	t[j] = n;
	t[j + 1] = NULL;
	free(*env);
	*env = t;
}

int	ft_env_count_var(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

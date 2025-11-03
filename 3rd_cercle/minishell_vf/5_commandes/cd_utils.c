/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:07:59 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/26 20:46:19 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cd_append(char ***penv, char *var, char *a)
{
	char	**env;
	char	**t;
	char	*v;
	int		i;

	env = *penv;
	i = 0;
	while (env && env[i])
		i++;
	t = (char **)realloc(env, (i + 2) * sizeof(*t));
	if (!t)
		return (0);
	*penv = t;
	v = ft_cmd_cd_create(var, a);
	if (!v)
		return (0);
	t[i] = v;
	t[i + 1] = NULL;
	return (1);
}

char	*ft_cmd_cd_create(char *var, char *a)
{
	size_t	i;
	size_t	j;
	char	*kv;

	i = ft_strlen(var);
	j = ft_strlen(a);
	kv = (char *)malloc(i + 1 + j + 1);
	if (!kv)
		return (NULL);
	ft_memcpy(kv, var, i);
	kv[i] = '=';
	ft_memcpy(kv + i + 1, a, j);
	kv[i + 1 + j] = '\0';
	return (kv);
}

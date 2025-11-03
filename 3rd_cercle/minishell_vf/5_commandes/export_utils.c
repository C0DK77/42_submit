/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:29:32 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/27 15:59:34 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_export_env(char ***env, char *a, char *s)
{
	char	**penv;
	char	**t;
	char	*val;
	int		i;

	if (ft_env_replace_var(env, a, s))
		return (1);
	penv = *env;
	i = 0;
	while (penv && penv[i])
		i++;
	t = (char **)realloc(penv, (i + 2) * sizeof(*t));
	if (!t)
		return (0);
	*env = t;
	val = ft_cmd_export_make_kv(a, s);
	if (!val)
		return (0);
	t[i] = val;
	t[i + 1] = NULL;
	return (1);
}

char	*ft_cmd_export_make_kv(char *a, char *s)
{
	size_t	i;
	size_t	j;
	char	*n;

	i = ft_strlen(a);
	j = ft_strlen(s);
	n = (char *)malloc(i + 1 + j + 1);
	if (!n)
		return (NULL);
	ft_memcpy(n, a, i);
	n[i] = '=';
	ft_memcpy(n + i + 1, s, j);
	n[i + 1 + j] = '\0';
	return (n);
}

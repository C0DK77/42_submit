/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:07:59 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/25 06:56:03 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_cd_append(char ***penv, char *var, char *a)
{
	char	**env;
	char	**tmp;
	char	*nv;
	int		i;

	env = *penv;
	i = 0;
	while (env && env[i])
		i++;
	tmp = (char **)realloc(env, (i + 2) * sizeof(*tmp));
	if (!tmp)
		return (0);
	*penv = tmp;
	nv = make_env_kv_cd(var, a);
	if (!nv)
		return (0);
	tmp[i] = nv;
	tmp[i + 1] = NULL;
	return (1);
}

char	*ft_cmd_cd_create(char *var, char *a)
{
	size_t	ln;
	size_t	lv;
	char	*kv;

	ln = ft_strlen(var);
	lv = ft_strlen(a);
	kv = (char *)malloc(ln + 1 + lv + 1);
	if (!kv)
		return (NULL);
	ft_memcpy(kv, var, ln);
	kv[ln] = '=';
	ft_memcpy(kv + ln + 1, a, lv);
	kv[ln + 1 + lv] = '\0';
	return (kv);
}

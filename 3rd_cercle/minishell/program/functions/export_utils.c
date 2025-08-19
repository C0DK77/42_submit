/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:10:51 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 15:36:27 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_export_check_value(t_envp **l, char *n, char *a, int i)
{
	char	*v;

	if (a == NULL)
		return (ft_env_set(l, n, NULL, 1), free(n), 1);
	v = ft_strdup(a);
	if (!v)
		return (free(n), 0);
	if (!ft_export_value(l, v, n, &i))
		return (free(n), 0);
	free(n);
	return (1);
}

int	ft_export_value(t_envp **l, char *v, char *n, int *i)
{
	t_envp	*e;
	char	*a;

	if (!v)
		return (0);
	if (i && *i)
	{
		e = ft_env_search_node(*l, n);
		if (e && e->value)
		{
			a = ft_strjoin(e->value, v);
			free(v);
			if (!a)
				return (0);
			v = a;
		}
	}
	ft_env_set(l, n, v, 1);
	return (free(v), 1);
}

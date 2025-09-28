/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:33:10 by ecid              #+#    #+#             */
/*   Updated: 2025/09/28 23:34:49 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Pour ft_cd_conditions
static char	*ft_cd_no_arg(t_envp *l)
{
	if (!ft_cd_search_var(l, "HOME"))
		return (NULL);
	return (ft_env_search_value(l, "HOME"));
}

static char	*ft_cd_with_arg(char *arg, t_envp *l)
{
	if (ft_strcmp(arg, "-") == 0)
	{
		if (!ft_cd_search_var(l, "OLDPWD"))
			return (NULL);
		return (ft_env_search_value(l, "OLDPWD"));
	}
	else if (ft_strcmp(arg, "--") == 0)
	{
		if (!ft_cd_search_var(l, "HOME"))
			return (NULL);
		return (ft_env_search_value(l, "HOME"));
	}
	else if (arg[0] == '-' && arg[1] != '\0')
		return (ft_cd_error(2, arg));
	return (arg);
}

char	*ft_cd_conditions(char **s, t_envp *l, char *target, int i)
{
	if (i > 2)
		return (ft_cd_error(0, NULL));
	if (i == 1)
		target = ft_cd_no_arg(l);
	else if (i > 1 && s[1])
		target = ft_cd_with_arg(s[1], l);
	else
		return (NULL);
	return (target);
}

int	ft_cd_search_var(t_envp *l, char *v)
{
	char	*t;

	t = ft_env_search_value(l, v);
	if (!t)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(v, 2);
		ft_putstr_fd(" not set\n", 2);
		return (0);
	}
	if (ft_strcmp(v, "OLDPWD") == 0)
	{
		ft_putstr_fd(t, 1);
		ft_putstr_fd("\n", 1);
	}
	return (1);
}

char	*ft_cd_error(int i, char *c)
{
	if (i == 0)
	{
		g_exit_status = 1;
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
	}
	if (i == 1)
	{
		g_exit_status = 1;
		return (perror("minishell: cd"), NULL);
	}
	if (i == 2)
	{
		g_exit_status = 2;
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(c, 2),
			ft_putstr_fd(": invalid option\n", 2),
			ft_putstr_fd("cd: usage: cd [dir]\n", 2), NULL);
	}
	return (NULL);
}

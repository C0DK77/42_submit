/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:22:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 20:09:37 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **s, t_envp *l)
{
	int		i;
	char	*target;
	char	*pwd_before;

	target = NULL;
	pwd_before = ft_env_search_value(l, "PWD");
	i = 0;
	while (s[i])
		i++;
	if (i == 1)
	{
		if (!ft_cd_search_var(l, "HOME"))
			return (1);
	}
	else
	{
		if (ft_strcmp(s[1], "-") == 0)
		{
			if (!ft_cd_search_var(l, "OLDPWD"))
				return (1);
		}
		else if (ft_strcmp(s[1], "--") == 0)
		{
			if (i == 2)
			{
				if (!ft_cd_search_var(l, "HOME"))
					return (1);
			}
			else if (i == 3)
				target = s[2];
			else
				return (ft_cd_error(1, NULL));
		}
		else if (s[1][0] == '-' && s[1][1] != '\0')
			return (ft_cd_error(2, s[1]));
		else
			target = s[1];
	}
	if (chdir(target) != 0)
		return (ft_cd_error(1, NULL));
	update_pwd_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
}

int	ft_cd_search_var(t_envp *l, char *v)
{
	v = ft_env_search_value(l, v);
	if (!v)
	{
		g_exit_status = 1;
		fprintf(stderr, "minishell: cd: %s not set\n", v);
		return (0);
	}
	if (ft_strcmp(v, "OLDPWD"))
		printf("%s\n", v);
	return (1);
}

int	ft_cd_error(int i, char *c)
{
	if (i == 0)
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	if (i == 1)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	if (i == 2)
	{
		fprintf(stderr, "minishell: cd: %s: invalid option\n", c);
		fprintf(stderr, "cd: usage: cd [dir]\n");
		g_exit_status = 2;
		return (1);
	}
	return (1);
}

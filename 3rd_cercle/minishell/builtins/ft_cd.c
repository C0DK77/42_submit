/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:42:34 by ecid              #+#    #+#             */
/*   Updated: 2025/08/17 16:42:59 by ecid             ###   ########.fr       */
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
		target = ft_env_search_value(l, "HOME");
		if (!target)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			g_exit_status = 1;
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(s[1], "-") == 0)
		{
			target = ft_env_search_value(l, "OLDPWD");
			if (!target)
			{
				fprintf(stderr, "minishell: cd: OLDPWD not set\n");
				g_exit_status = 1;
				return (1);
			}
			printf("%s\n", target);
		}
		else if (ft_strcmp(s[1], "--") == 0)
		{
			if (i == 2)
			{
				target = ft_env_search_value(l, "HOME");
				if (!target)
				{
					fprintf(stderr, "minishell: cd: HOME not set\n");
					g_exit_status = 1;
					return (1);
				}
			}
			else if (i == 3)
				target = s[2];
			else
			{
				fprintf(stderr, "minishell: cd: too many arguments\n");
				g_exit_status = 1;
				return (1);
			}
		}
		else if (s[1][0] == '-' && s[1][1] != '\0')
		{
			fprintf(stderr, "minishell: cd: %s: invalid option\n", s[1]);
			fprintf(stderr, "cd: usage: cd [dir]\n");
			g_exit_status = 2;
			return (1);
		}
		else
		{
			if (i > 2)
			{
				fprintf(stderr, "minishell: cd: too many arguments\n");
				g_exit_status = 1;
				return (1);
			}
			target = s[1];
		}
	}
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	update_pwd_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
}

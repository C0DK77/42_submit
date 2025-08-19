/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:22:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/19 01:37:01 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
			g_exit_status = 1;
			return (fprintf(stderr, "minishell: cd: HOME not set\n"), 1);
		}
	}
	else
	{
		if (ft_strcmp(s[1], "-") == 0)
		{
			target = ft_env_search_value(l, "OLDPWD");
			if (!target)
			{
				g_exit_status = 1;
				return (fprintf(stderr, "minishell: cd: OLDPWD not set\n"), 1);
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
				return (ft_cd_error(1, NULL));
		}
		else if (s[1][0] == '-' && s[1][1] != '\0')
			return (ft_cd_error(2, s[1]));
		else
		{
			if (i > 2)
				return (ft_cd_error(0, NULL));
			target = s[1];
		}
	}
	if (chdir(target) != 0)
		return (ft_cd_error(1, NULL));
	update_pwd_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
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

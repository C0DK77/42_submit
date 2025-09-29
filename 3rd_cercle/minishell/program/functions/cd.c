/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:22:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 07:00:16 by codk             ###   ########.fr       */
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
	target = ft_cd_conditions(s, l, i);
	if (!target)
		return (1);
	if (chdir(target) != 0)
		return (ft_cd_error(1, NULL), 1);
	ft_pwd_update_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
}

char	*ft_cd_conditions(char **s, t_envp *l, int i)
{
	if (i > 2)
		return (ft_cd_error(0, NULL));
	if (i == 1 && !ft_cd_search_var(l, "HOME"))
		return (NULL);
	if (i == 1)
		return (ft_env_search_value(l, "HOME"));
	if (ft_strcmp(s[1], "-") == 0 && !ft_cd_search_var(l, "OLDPWD"))
		return (NULL);
	if (ft_strcmp(s[1], "-") == 0)
		return (ft_env_search_value(l, "OLDPWD"));
	if (ft_strcmp(s[1], "--") == 0 && !ft_cd_search_var(l, "HOME"))
		return (NULL);
	if (ft_strcmp(s[1], "--") == 0)
		return (ft_env_search_value(l, "HOME"));
	if (s[1][0] == '-' && s[1][1] != '\0')
		return (ft_cd_error(2, s[1]));
	return (s[1]);
}

int	ft_cd_search_var(t_envp *l, char *v)
{
	char	*t;

	t = ft_env_search_value(l, v);
	if (!t)
	{
		g_exit_status = 1;
		return (ft_putall_fd(2, 3, "minishell: cd: ", v, " not set\n"), 0);
	}
	if (ft_strcmp(v, "OLDPWD") == 0)
		printf("%s\n", t);
	return (1);
}

char	*ft_cd_error(int i, char *c)
{
	if (i == 0)
	{
		g_exit_status = 1;
		return (ft_putstr_fd("minishell: cd: trop d'arguments\n", 2), NULL);
	}
	if (i == 1)
	{
		g_exit_status = 1;
		return (perror("minishell: cd"), NULL);
	}
	if (i == 2)
	{
		g_exit_status = 2;
		return (ft_putall_fd(2, 4, "minishell: cd: ", c, ": invalid option\n",
				"cd: usage: cd [dir]\n"), NULL);
	}
	return (NULL);
}

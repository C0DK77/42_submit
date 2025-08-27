/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:22:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/27 19:45:42 by corentindes      ###   ########.fr       */
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
	if (!ft_cd_conditions(s, l, target, i))
		return (1);
	else
		target = ft_cd_conditions(s, l, target, i);
	if (chdir(target) != 0)
	{
		ft_cd_error(1, NULL);
		return (1);
	}
	update_pwd_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
}

char	*ft_cd_conditions(char **s, t_envp *l, char *target, int i)
{
	if (i == 1 && !ft_cd_search_var(l, "HOME"))
		return (NULL);
	else
	{
		if (ft_strcmp(s[1], "-") == 0 && !ft_cd_search_var(l, "OLDPWD"))
			return (NULL);
		else if (i == 2 && ft_strcmp(s[1], "--") == 0 && !ft_cd_search_var(l,
				"HOME"))
			return (NULL);
		else if (i == 3 && ft_strcmp(s[1], "--") == 0)
			target = s[2];
		else if (ft_strcmp(s[1], "--") == 0)
			return (ft_cd_error(1, NULL));
		else if (s[1][0] == '-' && s[1][1] != '\0')
			return (ft_cd_error(2, s[1]));
		else
			target = s[1];
	}
	return (target);
}

int	ft_cd_search_var(t_envp *l, char *v)
{
	char	*t;

	t = ft_env_search_value(l, v);
	if (!t)
	{
		g_exit_status = 1;
		return (ft_putall_fd(2, 3, "minishell: cd: ", v, "not set\n"), 0);
	}
	if (ft_strcmp(t, "OLDPWD"))
		printf("%s\n", t);
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
		return (ft_putall_fd(2, 4, "minishell: cd: ", c, ": invalid option\n",
				"cd: usage: cd [dir]\n"), NULL);
	}
	return (NULL);
}

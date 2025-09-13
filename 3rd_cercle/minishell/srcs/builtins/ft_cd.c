/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:22:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/13 15:36:10 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_len(char **av)
{
	int	n;

	n = 0;
	if (!av)
		return (0);
	while (av[n])
		n++;
	return (n);
}

int	ft_cd(char **s, t_envp *l)
{
	char	*target;
	char	*pwd_before;
	int		argc;

	argc = args_len(s);
	pwd_before = ft_env_search_value(l, "PWD");
	target = ft_cd_conditions(s, l, NULL, argc);
	if (target == NULL)
		return (1);
	if (chdir(target) != 0)
		return (ft_cd_error(1, NULL), 1);
	update_pwd_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
}

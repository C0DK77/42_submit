/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:33:10 by ecid              #+#    #+#             */
/*   Updated: 2025/09/26 19:46:25 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_resolve_path(char **s, t_envp *l)
{
	char	*p;

	if (!s || !s[0] || s[0][0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	if (ft_strchr(s[0], '/'))
		p = ft_strdup(s[0]);
	else
		p = ft_exec_find_cmd(s[0], l);
	if (!p)
	{
		ft_putall_fd(2, 3, "minishell: ", s[0], ": command not found\n");
		exit(127);
	}
	return (p);
}

static void	ft_validate_target(char *p, char *cmd)
{
	if (access(p, F_OK) != 0)
	{
		ft_putall_fd(2, 3, "minishell: ", cmd, ": No such file or directory\n");
		free(p);
		exit(127);
	}
	if (ft_exec_is_directory(p))
	{
		ft_putall_fd(2, 3, "minishell: ", cmd, ": is a directory\n");
		free(p);
		exit(126);
	}
	if (access(p, X_OK) != 0)
	{
		ft_putall_fd(2, 3, "minishell: ", cmd, ": Permission denied\n");
		free(p);
		exit(126);
	}
}

void	ft_exec_cmd(char **s, t_envp *l)
{
	char	*p;
	char	**env;

	p = ft_resolve_path(s, l);
	ft_validate_target(p, s[0]);
	env = ft_exec_env_array(l);
	execve(p, s, env);
	perror("minishell");
	ft_free_tab(env);
	free(p);
	exit(126);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:39:39 by codk              #+#    #+#             */
/*   Updated: 2025/10/31 13:22:39 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_exec_path_res(char *cmd, char **env)
{
	char	*path;
	char	*s;
	char	*res;

	path = ft_env_search_value(env, "PATH");
	if (!path || !*path)
		return (NULL);
	s = ft_strdup(path);
	if (!s)
		return (NULL);
	res = ft_exec_path_dir(s, cmd);
	return (free(s), res);
}

int	ft_exec_isdirectory(char *p)
{
	struct stat	st;

	if (!p)
		return (0);
	if (stat(p, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

char	*ft_exec_path_dir(char *s, char *cmd)
{
	char	*dir;
	char	*sep;
	char	*res;

	dir = s;
	while (dir)
	{
		sep = ft_strchr(dir, ':');
		if (sep)
			*sep = '\0';
		if (*dir)
		{
			res = ft_join_path(dir, cmd);
			if (!res)
				return (NULL);
			if (access(res, X_OK) == 0)
				return (res);
			free(res);
		}
		if (!sep)
			break ;
		dir = sep + 1;
	}
	return (NULL);
}

void	ft_exec_print_error_1(char *path, char *s, int e)
{
	char	*a;

	if (!s || s[0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		e = ENOENT;
		return ;
	}
	a = s;
	if (path)
		a = path;
	if (s && ft_strchr(s, '/') == NULL)
	{
		if (e == ENOENT)
			ft_putall_fd(2, 3, "minishell: ", s, " : command not found\n");
		else
			ft_putall_fd(2, 4, s, ": ", strerror(e), "\n");
		return ;
	}
	ft_exec_print_error_2(a, e);
}

void	ft_exec_print_error_2(char *a, int e)
{
	if (!a)
		a = "(null)";
	if (e == EISDIR)
		ft_putall_fd(2, 2, a, ": Is a directory\n");
	else if (e == ENOENT)
		ft_putall_fd(2, 2, a, ": No such file or directory\n");
	else if (e == EACCES)
		ft_putall_fd(2, 2, a, ": Permission denied\n");
	else if (e == ENOTDIR)
		ft_putall_fd(2, 2, a, ": Not a directory\n");
	else if (e == ENOEXEC)
		ft_putall_fd(2, 2, a, ": Exec format error\n");
	else
		ft_putall_fd(2, 4, a, ": ", strerror(e), "\n");
}

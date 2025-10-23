/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_norme2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:39:30 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 08:44:05 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exec_checked_path(char *path, char **argv, t_shell *sh,
		int need_free)
{
	int	e;

	if (is_directory(path))
	{
		errno = EISDIR;
		if (need_free)
			free(path);
		return (-1);
	}
	execve(path, argv, sh->env);
	if (need_free)
	{
		e = errno;
		free(path);
		errno = e;
	}
	return (-1);
}

int	exec_with_path(char **argv, t_shell *sh)
{
	char	*full;

	if (!argv || !argv[0])
	{
		errno = EINVAL;
		return (-1);
	}
	if (argv[0][0] == '\0')
	{
		errno = ENOENT;
		return (-1);
	}
	if (ft_strchr(argv[0], '/'))
		return (exec_checked_path((char *)argv[0], argv, sh, 0));
	full = resolve_in_path(argv[0], sh->env);
	if (full)
		return (exec_checked_path(full, argv, sh, 1));
	errno = ENOENT;
	return (-1);
}

int	is_simple_builtin_type(t_type_cmd c)
{
	return (c == T_ECHO || c == T_PWD || c == T_CD || c == T_EXPORT
		|| c == T_UNSET || c == T_ENV || c == T_EXIT);
}

int	is_builtin_cmd(t_type_cmd c)
{
	return (is_simple_builtin_type(c));
}

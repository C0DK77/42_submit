/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:39:30 by codk              #+#    #+#             */
/*   Updated: 2025/10/31 13:22:13 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_child_fds(t_command *cmd, int i, int j, t_shell *sh)
{
	t_ios	ios;

	if (i >= 0 && dup2(i, STDIN_FILENO) < 0)
		return (perror("dup2"), 0);
	if (!ft_redir_fds(cmd->element, &ios, sh))
		return (0);
	if (j >= 0 && dup2(j, STDOUT_FILENO) < 0)
		return (perror("dup2"), ft_redir_close(&ios), 0);
	if (!ft_redir_apply_2(&ios))
		return (ft_redir_close(&ios), 0);
	if (i >= 0)
		close(i);
	if (j >= 0)
		close(j);
	return (ft_redir_close(&ios), 1);
}

void	ft_exec_child(t_command *cmd, t_shell *sh, t_all *all)
{
	char	**argv;
	size_t	argc;

	if (cmd->cmd == T_ECHO || cmd->cmd == T_PWD || cmd->cmd == T_CD
		|| cmd->cmd == T_EXPORT || cmd->cmd == T_UNSET || cmd->cmd == T_ENV
		|| cmd->cmd == T_EXIT)
		_exit(ft_exec_cmd(cmd, sh, all));
	argc = ft_count_arg(cmd->element);
	if (argc == 0)
		_exit(0);
	argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		_exit(0);
	if (!ft_fill_argv(cmd, argv))
	{
		free(argv);
		_exit(0);
	}
	if (ft_exec_path(argv, sh) < 0)
		ft_exec_handle_error(argv);
}

int	ft_exec_path(char **argv, t_shell *sh)
{
	char	*s;

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
		return (ft_exec_path_check((char *)argv[0], argv, sh, 0));
	s = ft_exec_path_res(argv[0], sh->env);
	if (s)
		return (ft_exec_path_check(s, argv, sh, 1));
	errno = ENOENT;
	return (-1);
}

void	ft_exec_handle_error(char **argv)
{
	int	e;
	int	code;

	e = errno;
	code = 126;
	ft_exec_print_error_1(NULL, argv[0], e);
	if (e == ENOENT)
		code = 127;
	ft_free_argv(argv);
	_exit(code);
}

int	ft_exec_path_check(char *path, char **argv, t_shell *sh, int i)
{
	int	e;

	if (ft_exec_isdirectory(path))
	{
		errno = EISDIR;
		if (i)
			free(path);
		return (-1);
	}
	execve(path, argv, sh->env);
	if (i)
	{
		e = errno;
		free(path);
		errno = e;
	}
	return (-1);
}

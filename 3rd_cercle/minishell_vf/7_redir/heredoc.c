/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:31 by codk              #+#    #+#             */
/*   Updated: 2025/12/02 17:24:14 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(char *s, t_shell *sh)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), sh->last_exit = 1,
			-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[0]);
		ft_heredoc_process(fd, s);
	}
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	if (waitpid(pid, &status, 0) == -1)
		return (close(fd[0]), ft_signal_init(), sh->last_exit = 1, -1);
	return (ft_signal_init(), ft_heredoc_status(status, fd[0], sh));
}

void	ft_heredoc_process(int *fd, char *a)
{
	char	*s;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		s = readline("> ");
		if (!s)
		{
			ft_putall_fd(2, 3, WARNING, a, "')");
			break ;
		}
		if (ft_strcmp(s, a) == 0)
		{
			free(s);
			break ;
		}
		ft_putendl_fd(s, fd[1]);
		free(s);
	}
	close(fd[1]);
	_exit(0);
}

int	ft_heredoc_status(int status, int fd, t_shell *sh)
{
	if (WIFSIGNALED(status))
	{
		ft_putendl_fd("", 2);
		sh->last_exit = 128 + WTERMSIG(status);
		return (close(fd), -1);
	}
	else if (WIFEXITED(status))
		sh->last_exit = WEXITSTATUS(status);
	return (fd);
}

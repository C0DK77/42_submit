/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 00:26:28 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_stdio(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

static void	child_exec(t_parsing *p, t_envp **l, int prev_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (p->sep == SEP_PIPE)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (ft_exec_redirections_init(p, *l) != 0)
		exit(1);
	reset_signals();
	signal(SIGINT, ft_handler_exec);
	signal(SIGQUIT, ft_handler_exec);
	signal(SIGPIPE, SIG_DFL);
	if (ft_exec_builtin(p->line, l))
		exit(g_exit_status);
	ft_exec_cmd(p->line, *l);
	exit(1);
}

static void	do_one(t_parsing **pp, t_envp **l, int *prev_fd, pid_t *last_pid,
		int fd[2])
{
	if ((*pp)->prev && (((*pp)->prev->sep == SEP_AND_IF && g_exit_status != 0)
			|| ((*pp)->prev->sep == SEP_OR_IF && g_exit_status == 0)))
	{
		*pp = (*pp)->next;
		return ;
	}
	if ((*pp)->sep == SEP_NONE)
	{
		if (ft_exec_redirections_init(*pp, *l) != 0)
			exit(1);
		if (ft_exec_builtin((*pp)->line, l))
		{
			*pp = (*pp)->next;
			return ;
		}
	}
	if ((*pp)->sep == SEP_PIPE)
		pipe(fd);
	*last_pid = fork();
	if (*last_pid == 0)
		child_exec(*pp, l, *prev_fd, fd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if ((*pp)->sep == SEP_PIPE)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
	*pp = (*pp)->next;
}

static void	wait_children(pid_t last_pid)
{
	int		status;
	pid_t	w;

	while (1)
	{
		w = wait(&status);
		if (w == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (w == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
	if (g_exit_status == 131)
		printf("Quit (core dump)\n");
}

void	ft_exec(t_parsing *p, t_envp **l)
{
	int		fd[2];
	int		prev_fd;
	int		s_stdin;
	int		s_stdout;
	pid_t	last_pid;

	prev_fd = -1;
	save_stdio(&s_stdin, &s_stdout);
	last_pid = -1;
	while (p)
		do_one(&p, l, &prev_fd, &last_pid, fd);
	wait_children(last_pid);
	dup2(s_stdin, STDIN_FILENO);
	dup2(s_stdout, STDOUT_FILENO);
	close(s_stdin);
	close(s_stdout);
}

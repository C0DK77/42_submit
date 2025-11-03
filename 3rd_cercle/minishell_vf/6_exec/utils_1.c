/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:39:00 by codk              #+#    #+#             */
/*   Updated: 2025/10/31 11:09:33 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_cmd(t_command *cmd, t_shell *sh, t_all *all)
{
	if (cmd->cmd == T_ECHO)
		return (ft_cmd_echo(cmd, sh));
	if (cmd->cmd == T_PWD)
		return (ft_cmd_pwd(cmd, sh));
	if (cmd->cmd == T_CD)
		return (ft_cmd_cd(cmd, sh));
	if (cmd->cmd == T_EXPORT)
		return (ft_cmd_export(cmd, sh));
	if (cmd->cmd == T_UNSET)
		return (ft_cmd_unset(cmd, sh));
	if (cmd->cmd == T_ENV)
		return (ft_cmd_env(cmd, sh));
	if (cmd->cmd == T_EXIT)
		return (ft_cmd_exit(cmd, sh, all));
	return (127);
}

int	ft_exec_cmd_one(t_command *cmd, int *i, t_launch_ctx *ctx)
{
	t_pipeinfo	pi;
	pid_t		p;

	pi.need_pipe = (cmd->next != NULL);
	pi.out_wr = -1;
	if (pi.need_pipe)
	{
		if (pipe(pi.pfd) < 0)
		{
			perror("pipe");
			if (*i >= 0)
				close(*i);
			return (1);
		}
		pi.out_wr = pi.pfd[1];
	}
	p = ft_exec_cmd_one_spawn(cmd, *i, pi.out_wr, ctx->sh);
	if (p < 0)
		return (ft_exec_clean(i, &pi), 1);
	ctx->pids[*ctx->out_n] = p;
	*ctx->out_n = *ctx->out_n + 1;
	return (ft_exec_pipe_state(i, &pi), 0);
}

pid_t	ft_exec_cmd_one_spawn(t_command *cmd, int i, int j, t_shell *sh)
{
	pid_t	p;
	t_all	*all;

	all = ft_init_all(0);
	p = fork();
	if (p < 0)
		return (perror("fork"), (pid_t)(-1));
	if (p == 0)
	{
		ft_signal_reset();
		if (!ft_exec_child_fds(cmd, i, j, sh))
			_exit(1);
		ft_exec_child(cmd, sh, all);
		_exit(127);
	}
	return (p);
}

void	ft_exec_clean(int *i, t_pipeinfo *pi)
{
	if (*i >= 0)
		close(*i);
	if (pi->need_pipe)
	{
		close(pi->out_wr);
		close(pi->pfd[0]);
	}
}

void	ft_exec_pipe_state(int *i, t_pipeinfo *pi)
{
	if (*i >= 0)
		close(*i);
	if (pi->need_pipe)
	{
		*i = pi->pfd[0];
		close(pi->out_wr);
	}
	else
		*i = -1;
}

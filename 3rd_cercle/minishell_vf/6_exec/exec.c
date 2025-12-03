/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:24 by codk              #+#    #+#             */
/*   Updated: 2025/12/03 12:26:49 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_init(t_all *all, t_command *cmd, t_shell *sh)
{
	pid_t		p[256];
	int			i;
	t_command	*t;

	t = cmd;
	if (t && !t->next && (t->cmd == T_ECHO || t->cmd == T_PWD || t->cmd == T_CD
			|| t->cmd == T_EXPORT || t->cmd == T_UNSET || t->cmd == T_ENV
			|| t->cmd == T_EXIT))
	{
		if (t->cmd == T_EXIT && t->nb_args > 2)
			return (ft_putall_fd(2, 2, EXIT, "too many arguments\n"), 1);
		return (ft_exec_cmd_single(t, sh, all));
	}
	if (ft_exec_cmd_all(cmd, sh, p, &i) != 0)
		return (1);
	ft_signal_config_last_exit(sh, p, i);
	return (ft_signal_init(), sh->last_exit);
}

int	ft_exec_cmd_single(t_command *cmd, t_shell *sh, t_all *all)
{
	int	saved_in;
	int	saved_out;
	int	code;

	if (!ft_exec_save_stdio(&saved_in, &saved_out))
		return (1);
	if (!ft_redir_apply_3(cmd, saved_in, saved_out, sh))
	{
		ft_exec_restore_stdio_and_close(saved_in, saved_out);
		return (1);
	}
	if (cmd->cmd == T_EXIT)
	{
		ft_exec_restore_stdio_and_close(saved_in, saved_out);
		return (ft_exec_cmd(cmd, sh, all));
	}
	code = ft_exec_cmd(cmd, sh, all);
	ft_exec_restore_stdio_and_close(saved_in, saved_out);
	sh->last_exit = code;
	return (code);
}

int	ft_exec_cmd_all(t_command *cmd, t_shell *sh, pid_t *p, int *out_n)
{
	int				i;
	t_command		*t;
	t_launch_ctx	ctx;

	i = -1;
	*out_n = 0;
	ctx.pids = p;
	ctx.out_n = out_n;
	ctx.sh = sh;
	t = cmd;
	while (t)
	{
		if (ft_exec_cmd_one(t, &i, &ctx))
		{
			if (i >= 0)
				close(i);
			return (1);
		}
		t = t->next;
	}
	if (i >= 0)
		close(i);
	return (0);
}

int	ft_exec_save_stdio(int *saved_in, int *saved_out)
{
	*saved_in = dup(STDIN_FILENO);
	*saved_out = dup(STDOUT_FILENO);
	if (*saved_in < 0 || *saved_out < 0)
	{
		perror("dup");
		if (*saved_in >= 0)
			close(*saved_in);
		if (*saved_out >= 0)
			close(*saved_out);
		return (0);
	}
	return (1);
}

void	ft_exec_restore_stdio_and_close(int saved_in, int saved_out)
{
	if (dup2(saved_in, STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(saved_out, STDOUT_FILENO) < 0)
		perror("dup2");
	if (saved_in >= 0)
		close(saved_in);
	if (saved_out >= 0)
		close(saved_out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:42:37 by codk              #+#    #+#             */
/*   Updated: 2025/10/28 10:25:46 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redir_fds(t_element *lmt, t_ios *ios, t_shell *sh)
{
	t_redir	*r;

	ios->in_fd = -1;
	ios->out_fd = -1;
	while (lmt)
	{
		if (lmt->kind == REDIR)
		{
			r = lmt->u_.redirs;
			while (r)
			{
				if (!ft_redir_apply_1(ios, r, sh))
					return (0);
				r = r->next;
			}
		}
		lmt = lmt->next;
	}
	return (1);
}

int	ft_redir_apply_1(t_ios *ios, t_redir *r, t_shell *sh)
{
	if (r->type == REDIR_IN || r->type == HEREDOC)
		return (ft_redir_set_in(ios, r, sh));
	if (r->type == REDIR_OUT || r->type == APPEND)
		return (ft_redir_set_out(ios, r));
	return (1);
}

int	ft_redir_apply_2(t_ios *ios)
{
	if (ios->in_fd >= 0)
		if (dup2(ios->in_fd, STDIN_FILENO) < 0)
			return (perror("dup2"), 0);
	if (ios->out_fd >= 0)
		if (dup2(ios->out_fd, STDOUT_FILENO) < 0)
			return (perror("dup2"), 0);
	return (1);
}

int	ft_redir_apply_3(t_command *cmd, int saved_in, int saved_out, t_shell *sh)
{
	t_ios	ios;

	if (!ft_redir_fds(cmd->element, &ios, sh))
	{
		if (saved_in >= 0)
			close(saved_in);
		if (saved_out >= 0)
			close(saved_out);
		return (0);
	}
	if (!ft_redir_apply_2(&ios))
	{
		ft_redir_close(&ios);
		if (saved_in >= 0)
			close(saved_in);
		if (saved_out >= 0)
			close(saved_out);
		return (0);
	}
	return (ft_redir_close(&ios), 1);
}

void	ft_redir_close(t_ios *ios)
{
	if (ios->in_fd >= 0)
	{
		close(ios->in_fd);
		ios->in_fd = -1;
	}
	if (ios->out_fd >= 0)
	{
		close(ios->out_fd);
		ios->out_fd = -1;
	}
}

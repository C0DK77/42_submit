/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 20:59:07 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_redir *r, t_envp *env, int *last_hd)
{
	int	tmp;

	tmp = ft_exec_create_heredoc(r->target, r->hd_quoted, env);
	if (tmp < 0)
	{
		if (*last_hd != -1)
			close_if_open(last_hd);
		if (tmp == -2)
			return (-2);
		return (1);
	}
	close_if_open(last_hd);
	*last_hd = tmp;
	return (0);
}

static int	handle_in(t_redir *r, int *fd_in)
{
	int	tmp;

	tmp = open(r->target, O_RDONLY);
	if (tmp < 0)
	{
		print_file_error(r->target);
		return (1);
	}
	close_if_open(fd_in);
	*fd_in = tmp;
	return (0);
}

static int	handle_out_or_append(t_redir *r, int *fd_out)
{
	int	flags;
	int	tmp;

	flags = O_CREAT | O_WRONLY;
	if (r->type == REDIR_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	tmp = open(r->target, flags, 0644);
	if (tmp < 0)
	{
		print_file_error(r->target);
		return (1);
	}
	close_if_open(fd_out);
	*fd_out = tmp;
	return (0);
}

static int	apply_fds(int last_hd, int fd_in, int fd_out)
{
	if (last_hd != -1)
	{
		if (dup2(last_hd, STDIN_FILENO) == -1)
			return (close(last_hd), 1);
		close(last_hd);
		close_if_open(&fd_in);
	}
	else if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (close(fd_in), 1);
		close(fd_in);
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (close(fd_out), 1);
		close(fd_out);
	}
	return (0);
}

int	ft_exec_redirections_init(t_parsing *s, t_envp *env)
{
	t_redir	*r;
	int		fd_in;
	int		fd_out;
	int		last_hd;
	int		ret;

	r = s->redirs;
	fd_in = -1;
	fd_out = -1;
	last_hd = -1;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
			ret = handle_heredoc(r, env, &last_hd);
		else if (r->type == REDIR_IN)
			ret = handle_in(r, &fd_in);
		else
			ret = handle_out_or_append(r, &fd_out);
		if (ret != 0)
			return (close_if_open(&fd_in), close_if_open(&fd_out), ret);
		r = r->next;
	}
	return (apply_fds(last_hd, fd_in, fd_out));
}

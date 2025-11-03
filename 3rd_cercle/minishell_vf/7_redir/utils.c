/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:40:38 by codk              #+#    #+#             */
/*   Updated: 2025/10/28 10:15:25 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redir_set_in(t_ios *ios, t_redir *r, t_shell *sh)
{
	int	fd;

	fd = -1;
	if (r->type == REDIR_IN)
	{
		fd = open(r->target, O_RDONLY);
		if (fd < 0)
			perror(r->target);
	}
	else if (r->type == HEREDOC)
		fd = ft_heredoc(r->target, sh);
	if (ios->in_fd >= 0)
		close(ios->in_fd);
	ios->in_fd = fd;
	if (fd < 0)
		return (0);
	return (1);
}

int	ft_redir_set_out(t_ios *ios, t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == REDIR_OUT)
	{
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(r->target);
	}
	else if (r->type == APPEND)
	{
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror(r->target);
	}
	return (ft_redir_replace_fd(&ios->out_fd, fd));
}

int	ft_redir_replace_fd(int *dst, int newfd)
{
	if (*dst >= 0)
		close(*dst);
	*dst = newfd;
	if (newfd < 0)
		return (0);
	return (1);
}

char	*ft_join_path(char *dir, char *cmd)
{
	size_t	dir_l;
	size_t	cmd_l;
	char	*s;

	dir_l = ft_strlen(dir);
	cmd_l = ft_strlen(cmd);
	s = (char *)malloc(dir_l + cmd_l + 2);
	if (!s)
		return (NULL);
	ft_memcpy(s, dir, dir_l);
	s[dir_l] = '/';
	ft_memcpy(s + dir_l + 1, cmd, cmd_l);
	s[dir_l + 1 + cmd_l] = '\0';
	return (s);
}

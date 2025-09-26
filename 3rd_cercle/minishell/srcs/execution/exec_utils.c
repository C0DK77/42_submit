/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 20:19:34 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* permission*/
static void	print_file_error(const char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	ft_exec_redirections_init(t_parsing *s, t_envp *env)
{
	t_redir	*r;
	int		fd_in;
	int		fd_out;
	int		last_heredoc_fd;
	int		flags;
	int		tmp_fd;

	r = s->redirs;
	fd_in = -1;
	fd_out = -1;
	last_heredoc_fd = -1;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
		{
			tmp_fd = ft_exec_create_heredoc(r->target, r->hd_quoted, env);
			if (tmp_fd < 0)
			{
				if (tmp_fd == -2)
				{
					if (last_heredoc_fd != -1)
						close(last_heredoc_fd);
					return (-2);
				}
				if (last_heredoc_fd != -1)
					close(last_heredoc_fd);
				return (1);
			}
			if (last_heredoc_fd != -1)
				close(last_heredoc_fd);
			last_heredoc_fd = tmp_fd;
		}
		else if (r->type == REDIR_IN)
		{
			tmp_fd = open(r->target, O_RDONLY);
			if (tmp_fd < 0)
			{
				print_file_error(r->target);
				return (1);
			}
			if (fd_in != -1)
				close(fd_in);
			fd_in = tmp_fd;
		}
		else if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
		{
			flags = O_CREAT | O_WRONLY | (r->type == REDIR_APPEND ? O_APPEND : O_TRUNC);
			tmp_fd = open(r->target, flags, 0644);
			if (tmp_fd < 0)
			{
				print_file_error(r->target);
				return (1);
			}
			if (fd_out != -1)
				close(fd_out);
			fd_out = tmp_fd;
		}
		r = r->next;
	}
	if (last_heredoc_fd != -1)
	{
		if (dup2(last_heredoc_fd, STDIN_FILENO) == -1)
		{
			close(last_heredoc_fd);
			return (1);
		}
		close(last_heredoc_fd);
		if (fd_in != -1)
			close(fd_in);
	}
	else if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			close(fd_in);
			return (1);
		}
		close(fd_in);
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			close(fd_out);
			return (1);
		}
		close(fd_out);
	}
	return (0);
}

int	ft_exec_is_directory(char *p)
{
	struct stat	st;

	if (stat(p, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

char	*ft_exec_find_cmd(char *s, t_envp *l)
{
	char	*v;
	char	**dirs;
	char	*full_path;
	int		i;

	v = ft_env_search_value(l, "PATH");
	if (!v)
		return (NULL);
	dirs = ft_split(v, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin_three(dirs[i], "/", s);
		if (full_path && access(full_path, X_OK) == 0)
		{
			ft_free_tab(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(dirs);
	return (NULL);
}

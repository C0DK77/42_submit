/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/30 16:45:32 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_exec_redirections_init(t_parsing *s)
{
	int	app;
	int	fd;
	int	i;

	i = 0;
	app = 0;
	if (ft_exec_heredoc(s, i))
		return (1);
	while (s->outfiles && s->outfiles[i])
	{
		if (s->append && s->append[i])
			app = 1;
		if (app)
			fd = open(s->outfiles[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(s->outfiles[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(s->outfiles[i]), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int	ft_exec_heredoc(t_parsing *s, int i)
{
	int	fd;

	if (s->heredoc)
	{
		dup2(s->heredoc_fd, STDIN_FILENO);
		close(s->heredoc_fd);
	}
	else
	{
		while (s->infiles && s->infiles[i])
		{
			fd = open(s->infiles[i], O_RDONLY);
			if (fd < 0)
				return (perror(s->infiles[i]), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
	}
	return (0);
}

int	ft_exec_create_heredoc(char *d)
{
	int		fd;
	char	*l;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc open"), -1);
	while (1)
	{
		l = readline("> ");
		if (!l)
			break ;
		if (ft_strcmp(l, d) == 0)
		{
			free(l);
			break ;
		}
		write(fd, l, ft_strlen(l));
		write(fd, "\n", 1);
		free(l);
	}
	return (close(fd), 0);
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
			return (ft_free_tab(dirs), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_tab(dirs), NULL);
}

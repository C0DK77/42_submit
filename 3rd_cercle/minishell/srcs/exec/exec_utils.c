/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/27 22:30:29 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_redirections_init(t_parsing *s)
{
	int	fd;
	int	i;
	int	app;

	if (s->heredoc)
	{
		i = 0;
		while (s->infiles && s->infiles[i + 1])
			i++;
		fd = ft_exec_create_heredoc(s->infiles[i]);
		if (fd == -2)
			return (1);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			close(fd);
			return (1);
		}
		close(fd);
	}
	else
	{
		i = 0;
		while (s->infiles && s->infiles[i])
		{
			fd = open(s->infiles[i], O_RDONLY);
			if (fd < 0)
			{
				perror(s->infiles[i]);
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup2 infile");
				close(fd);
				return (1);
			}
			close(fd);
			i++;
		}
	}
	i = 0;
	while (s->outfiles && s->outfiles[i])
	{
		app = 0;
		if (s->append && s->append[i])
			app = 1;
		if (app == 1)
			fd = open(s->outfiles[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(s->outfiles[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(s->outfiles[i]);
			return (1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 outfile");
			close(fd);
			return (1);
		}
		close(fd);
		i++;
	}
	return (0);
}

int	ft_exec_create_heredoc(char *delim)
{
	int		hd[2];
	pid_t	pid;
	int		st;

	if (pipe(hd) == -1)
		return (perror("heredoc pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("heredoc fork"), close(hd[0]), close(hd[1]), -1);
	if (pid == 0)
	{
		char	*l;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(hd[0]);
		while (1)
		{
			l = readline("> ");
			if (!l)
				break ;
			if (ft_strcmp(l, delim) == 0)
			{
				free(l);
				break ;
			}
			write(hd[1], l, ft_strlen(l));
			write(hd[1], "\n", 1);
			free(l);
		}
		close(hd[1]);
		_exit(0);
	}
	close(hd[1]);
	if (waitpid(pid, &st, 0) == -1)
		return (perror("heredoc waitpid"), close(hd[0]), -1);
	if (WIFSIGNALED(st) && WTERMSIG(st) == SIGINT)
	{
		g_exit_status = 130;
		close(hd[0]);
		return (-2);
	}
	return (hd[0]);
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
			return(full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tab(dirs);
	return(NULL);
}


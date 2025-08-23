/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/23 08:58:32 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_exec_redirections_init(t_parsing *s)
{
	int	app;

	int fd, i;
	if (s->heredoc)
	{
		i = 0;
		while (s->infiles && s->infiles[i + 1])
			i++;
		if (ft_exec_create_heredoc(s->infiles[i]) != 0)
			return (1);
		fd = open(HEREDOC_FILE, O_RDONLY);
		if (fd < 0)
			return (perror("heredoc open for reading"), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		i = 0;
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
	i = 0;
	while (s->outfiles && s->outfiles[i])
	{
		app = (s->append && s->append[i]) ? 1 : 0;
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

int	ft_exec_create_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("heredoc open"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
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
			ft_free_split(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

void	ft_free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_pwd_export_env_set(t_envp **l, char *s, char *value, int i)
{
	t_envp	*t;
	t_envp	*n;

	t = *l;
	while (t)
	{
		if (ft_strcmp(t->var, s) == 0)
		{
			if (value)
			{
				free(t->value);
				t->value = ft_strdup(value);
			}
			if (i)
				t->export = 1;
			return ;
		}
		t = t->next;
	}
	n = malloc(sizeof(t_envp));
	n->var = ft_strdup(s);
	n->value = value ? ft_strdup(value) : NULL;
	n->export = i;
	n->next = (*l)->next;
	(*l)->next = n;
}

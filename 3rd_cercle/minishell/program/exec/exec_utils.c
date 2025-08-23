/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 20:19:17 by corentindes      ###   ########.fr       */
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

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
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

char	**ft_env_to_tab(t_envp *l)
{
	int		i;
	t_envp	*t;
	char	**env_tab;
	char	*entry;

	i = 0;
	t = l;
	while (t)
	{
		i++;
		t = t->next;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	t = l;
	i = 0;
	while (t)
	{
		entry = ft_strjoin_three(t->var, "=", t->value);
		if (!entry)
		{
			ft_free_split(env_tab);
			return (NULL);
		}
		env_tab[i++] = entry;
		t = t->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	ft_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_env_set(t_envp **l, char *s, char *value, int i)
{
	t_envp	*t;
	t_envp	*n;

	t = *l;
	while (t)
	{
		if (strcmp(t->var, s) == 0)
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

void	ft_env_sorted(t_envp *envp)
{
	int		i;
	t_envp	*tmp;
	t_envp	*arr[1000];

	i = 0;
	while (envp && i < 1000)
	{
		arr[i++] = envp;
		envp = envp->next;
	}
	for (int j = 0; j < i - 1; j++)
	{
		for (int k = j + 1; k < i; k++)
		{
			if (ft_strcmp(arr[j]->var, arr[k]->var) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[k];
				arr[k] = tmp;
			}
		}
	}
	for (int j = 0; j < i; j++)
	{
		printf("declare -x %s", arr[j]->var);
		if (arr[j]->value)
			printf("=\"%s\"", arr[j]->value);
		printf("\n");
	}
}

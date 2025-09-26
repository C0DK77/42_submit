/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_create_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 20:33:28 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* traite $? */
static int	expand_status(int fd, size_t *i)
{
	char	*tmp;

	tmp = ft_itoa((int)g_exit_status);
	if (!tmp)
		return (0);
	if (write(fd, tmp, ft_strlen(tmp)) < 0)
		return (free(tmp), 0);
	free(tmp);
	(*i)++;
	return (1);
}

/* traite $NAME — ≤ 25 lignes */
static int	expand_name(int fd, const char *s, size_t *i, t_envp *env)
{
	size_t	start;
	char	*name;
	char	*val;

	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	name = ft_substr(s, (unsigned int)start, (size_t)(*i - start));
	if (!name)
		return (0);
	val = ft_env_search_value(env, name);
	if (val && write(fd, val, ft_strlen(val)) < 0)
		return (free(name), 0);
	free(name);
	return (1);
}

static int	write_expanded_line(int fd, const char *s, t_envp *env)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
			{
				if (!expand_status(fd, &i))
					return (0);
			}
			else if (ft_isalpha(s[i]) || s[i] == '_')
			{
				if (!expand_name(fd, s, &i, env))
					return (0);
			}
			else if (write(fd, "$", 1) < 0)
				return (0);
		}
		else if (write(fd, &s[i++], 1) < 0)
			return (0);
	}
	return (1);
}

static void	heredoc_child(int hd[2], char *delim, int quoted, t_envp *env)
{
	char	*l;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(hd[0]);
	while (1)
	{
		l = readline("heredoc> ");
		if (!l)
			break ;
		if (ft_strcmp(l, delim) == 0)
			return (free(l), close(hd[1]), _exit(0));
		if (quoted)
		{
			if (write(hd[1], l, ft_strlen(l)) < 0)
				return (free(l), close(hd[1]), _exit(1));
		}
		else if (!write_expanded_line(hd[1], l, env))
			return (free(l), close(hd[1]), _exit(1));
		if (write(hd[1], "\n", 1) < 0)
			return (free(l), close(hd[1]), _exit(1));
		free(l);
	}
	close(hd[1]);
	_exit(0);
}

int	ft_exec_create_heredoc(char *delim, int quoted, t_envp *env)
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
		heredoc_child(hd, delim, quoted, env);
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

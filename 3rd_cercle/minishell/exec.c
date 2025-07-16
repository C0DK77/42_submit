/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/16 17:46:29 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_exec(t_parsing *p, t_envp *l)
{
	int		fd[2];
	pid_t	pid;

	while (p)
	{
		ft_exec_redirections_init(p);
		if (p->sep == SEP_NONE && ft_exec_builtin(p->line, &l))
		{
			p = p->next;
			continue ;
		}
		if (p->sep == SEP_PIPE)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (p->sep == SEP_PIPE)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			ft_exec_cmd(p->line, l);
			exit(1);
		}
		else
		{
			waitpid(pid, &g_exit_status, 0);
			if (p->sep == SEP_PIPE)
			{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
			}
		}
		p = p->next;
	}
}

void	ft_exec_cmd(char **s, t_envp *l)
{
	char	*path;
	char	**env;

	if (!s || !s[0])
		exit(0);
	if (s[0][0] == '/' || s[0][0] == '.')
		path = ft_strdup(s[0]);
	else
		path = ft_exec_find_cmd(s[0], l);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", s[0]);
		exit(127);
	}
	if (ft_exec_is_directory(path))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", path);
		free(path);
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		perror("minishell");
		free(path);
		exit(126);
	}
	env = ft_exec_env_array(l);
	execve(path, s, env);
	perror("execve");
	free(path);
	ft_free_split(env);
	exit(errno == ENOENT ? 127 : 126);
}

char	**ft_exec_env_array(t_envp *l)
{
	int		i;
	t_envp	*t;
	char	**env;
	char	*entry;

	i = 0;
	t = l;
	while (t)
	{
		i++;
		t = t->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	t = l;
	i = 0;
	while (t)
	{
		entry = ft_strjoin(t->var, "=");
		env[i] = ft_strjoin(entry, t->value);
		free(entry);
		i++;
		t = t->next;
	}
	env[i] = NULL;
	return (env);
}

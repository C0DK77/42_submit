/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/28 23:01:26 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_exec(t_parsing *p, t_envp *l)
{
	int		fd[2];
	int		prev_fd;
	int		saved_stdin;
	int		saved_stdout;
	pid_t	pid;

	prev_fd = -1;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (p)
	{
		if (p->prev && p->prev->sep == SEP_AND_IF && g_exit_status != 0)
		{
			p = p->next;
			continue ;
		}
		if (p->prev && p->prev->sep == SEP_OR_IF && g_exit_status == 0)
		{
			p = p->next;
			continue ;
		}
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
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (p->sep == SEP_PIPE)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			ft_exec_cmd(p->line, l);
			exit(1);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (p->sep == SEP_PIPE)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			else
			{
				waitpid(pid, &g_exit_status, 0);
				prev_fd = -1;
			}
		}
		p = p->next;
	}
	while (wait(NULL) > 0)
		;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
void	ft_exec_cmd(char **s, t_envp *l)
{
	char	*p;
	char	**env;

	if (!s || !s[0] || s[0][0] == '\0')
	{
		fprintf(stderr, "minishell: %s: command not found\n", s[0] ? s[0] : "");
		exit(127);
	}
	if (ft_strchr(s[0], '/'))
		p = ft_strdup(s[0]);
	else
		p = ft_exec_find_cmd(s[0], l);
	if (!p)
	{
		fprintf(stderr, "minishell: %s: command not found\n", s[0]);
		exit(127);
	}
	if (access(p, F_OK) != 0)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n", s[0]);
		free(p);
		exit(127);
	}
	if (ft_exec_is_directory(p))
	{
		fprintf(stderr, "minishell: %s: Is a directory\n", s[0]);
		free(p);
		exit(126);
	}
	if (access(p, X_OK) != 0)
	{
		fprintf(stderr, "minishell: %s: Permission denied\n", s[0]);
		free(p);
		exit(126);
	}
	env = ft_exec_env_array(l);
	execve(p, s, env);
	perror("minishell");
	ft_free_split(env);
	free(p);
	exit(126);
}

char	**ft_exec_env_array(t_envp *l)
{
	int		i;
	int		count;
	char	**env;
	char	*entry;
	t_envp	*t;

	i = 0;
	t = l;
	count = 0;
	while (t)
	{
		if (t->export && t->value)
			count++;
		t = t->next;
	}
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	t = l;
	i = 0;
	while (t)
	{
		if (t->export && t->value)
		{
			entry = ft_strjoin(t->var, "=");
			env[i] = ft_strjoin(entry, t->value);
			free(entry);
			i++;
		}
		t = t->next;
	}
	env[i] = NULL;
	return (env);
}

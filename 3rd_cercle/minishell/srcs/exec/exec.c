/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/10 21:52:14 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_parsing *p, t_envp **l)
{
    int		fd[2];
    int		prev_fd;
    int		s_stdin;
    int		s_stdout;
    int		status;
    pid_t	pid;
    pid_t	last_pid;

    prev_fd = -1;
    s_stdin = dup(STDIN_FILENO);
    s_stdout = dup(STDOUT_FILENO);
    last_pid = -1;
    while (p)
    {
        if ((p->prev && p->prev->sep == SEP_AND_IF && g_exit_status != 0)
            || (p->prev && p->prev->sep == SEP_OR_IF && g_exit_status == 0))
        {
            p = p->next;
            continue ;
        }
        if (p->sep == SEP_NONE)
        {
            if (ft_exec_builtin(p->line, l))
            {
                p = p->next;
                continue;
            }
        }
        if (p->sep == SEP_PIPE)
            pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            //  reset_signals();
            //signal(SIGPIPE, SIG_DFL);
		    signal(SIGINT, SIG_DFL);

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
            if (ft_exec_redirections_init(p,*l) != 0)
                exit(1);
            reset_signals();
            signal(SIGINT, ft_handler_exec);
            signal(SIGQUIT, ft_handler_exec);
            if (ft_exec_builtin(p->line, l))
                exit(g_exit_status);
            ft_exec_cmd(p->line, *l);
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
                prev_fd = -1;
            last_pid = pid;
        }
        p = p->next;
    }
    if (last_pid > 0)
    {
        waitpid(last_pid, &status, 0);
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_exit_status = 128 + WTERMSIG(status);
        if (g_exit_status == 131)
            printf("Quit (core dump)\n");
    }
    while (1)
    {
        int w = wait(NULL);
        if (w == -1)
        {
            if (errno == EINTR)
                continue;
            if (errno == ECHILD)
                break;
        }
    }
    dup2(s_stdin, STDIN_FILENO);
    dup2(s_stdout, STDOUT_FILENO);
    close(s_stdin);
    close(s_stdout);

}

void	ft_exec_cmd(char **s, t_envp *l)
{
	char	*p;
	char	**env;

	if (!s || !s[0] || s[0][0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	if (ft_strchr(s[0], '/'))
		p = ft_strdup(s[0]);
	else
		p = ft_exec_find_cmd(s[0], l);
	if (!p)
	{
		ft_putall_fd(2, 3, "minishell: ", s[0], ": command not found\n");
		exit(127);
	}
	if (access(p, F_OK) != 0)
	{
		ft_putall_fd(2, 3, "minishell: ", s[0],
			": No such file or directory\n");
		free(p);
		exit(127);
	}
	if (ft_exec_is_directory(p))
	{
		ft_putall_fd(2, 3, "minishell: ", s[0], ": is a directory\n");
		free(p);
		exit(126);
	}
	if (access(p, X_OK) != 0)
	{
		ft_putall_fd(2, 3, "minishell: ", s[0], ": Permission denied\n");
		free(p);
		exit(126);
	}
	env = ft_exec_env_array(l);
	execve(p, s, env);
	perror("minishell");
	ft_free_tab(env);
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

	t = l;
	count = 0;
	while (t)
	{
		if (t->export)
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
		if (t->export)
		{
			entry = ft_strjoin(t->var, "=");
			if (!entry)
				return (NULL);
			if (t->value)
			    env[i] = ft_strjoin(entry, t->value);
            else
                env[i] = ft_strjoin(entry, "");
			free(entry);
			if (!env[i])
				return (NULL);
			i++;
		}
		t = t->next;
	}
	env[i] = NULL;
	return (env);
}

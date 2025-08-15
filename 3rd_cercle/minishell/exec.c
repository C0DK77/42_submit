/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/15 21:24:25 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ft_exect*/
static void ft_exec_pipeline(t_parsing *p_head, t_envp *l)
{
    int         fds[2];
    int         prev_fd = -1;
    t_parsing   *p = p_head;
    pid_t       pid;

    while (p)
    {
        if (p->next)
        {
            if (pipe(fds) == -1)
            {
                perror("minishell");
                return;
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("minishell");
            return;
        }
        else if (pid == 0) 
        {
            reset_signals();
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (p->next)
            {
                dup2(fds[1], STDOUT_FILENO);
                close(fds[0]);
                close(fds[1]);
            }

            if (ft_exec_redirections_init(p) != 0)
                _exit(1);
            if (ft_exec_builtin(p->line, &l))
                _exit(g_exit_status);
            ft_exec_cmd(p->line, l);
            _exit(127);
        }
        else
        {
            if (prev_fd != -1)
                close(prev_fd);
            if (p->next)
            {
                close(fds[1]);
                prev_fd = fds[0];
            }
            p = p->next;
        }
    }
    while (wait(NULL) > 0);
}

static void ft_exec_child(t_parsing *cmd, t_envp *l, int fd_in, int fd_out)
{
    reset_signals();
    if (fd_in != STDIN_FILENO) { dup2(fd_in, STDIN_FILENO); close(fd_in); }
    if (fd_out != STDOUT_FILENO) { dup2(fd_out, STDOUT_FILENO); close(fd_out); }
    if (ft_exec_redirections_init(cmd) != 0) exit(1);
    if (ft_exec_builtin(cmd->line, &l)) exit(g_exit_status);
    ft_exec_cmd(cmd->line, l);
    exit(127);
}

static void ft_exec_parent(pid_t pid)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    waitpid(pid, &g_exit_status, 0);
    setup_signals();
}

static void ft_exec_single_cmd(t_parsing *p, t_envp *l, int prev_fd)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("minishell");
        return;
    }
    if (pid == 0)
    {
        if (prev_fd != -1)
        {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }
        ft_exec_child(p, l, STDIN_FILENO, STDOUT_FILENO);
    }
    else
        ft_exec_parent(pid);
}
void ft_exec(t_parsing *p, t_envp *l)
{
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    while (p)
    {
        if (p->prev && ((p->prev->sep == SEP_AND_IF && g_exit_status != 0) ||
                        (p->prev->sep == SEP_OR_IF  && g_exit_status == 0)))
        {
            p = p->next;
            continue;
        }
        if (p->sep == SEP_PIPE)
        {
            ft_exec_pipeline(p, l);

            while (p && p->sep == SEP_PIPE)
                p = p->next;
        }
        else
        {
            int b_saved_in  = dup(STDIN_FILENO);
            int b_saved_out = dup(STDOUT_FILENO);

            if (ft_exec_redirections_init(p) != 0)
            {
                g_exit_status = 1;
            }
            else if (ft_exec_builtin(p->line, &l))
            {

                dup2(b_saved_in,  STDIN_FILENO);
                dup2(b_saved_out, STDOUT_FILENO);
                close(b_saved_in);
                close(b_saved_out);

                p = p->next;
                continue; 
            }
            dup2(b_saved_in,  STDIN_FILENO);
            dup2(b_saved_out, STDOUT_FILENO);
            close(b_saved_in);
            close(b_saved_out);

            ft_exec_single_cmd(p, l, -1);
        }

        p = p->next;
    }
    while (wait(NULL) > 0)
    continue;
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



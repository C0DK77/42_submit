/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/04 21:41:50 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_redirections_init(t_parsing *s)
{
    t_redir *r = s->redirs;
    int fd_in = -1;
    int fd_out = -1;
    int first_heredoc_fd = -1;

    while (r)
    {
        if (r->type == REDIR_HEREDOC)
        {
            int tmp_fd = ft_exec_create_heredoc(r->target);
            if (tmp_fd < 0)
                return (1);
            if (first_heredoc_fd == -1)
                first_heredoc_fd = tmp_fd;
            else
                close(tmp_fd);
        }
        else if (r->type == REDIR_IN)
        {
            int tmp_fd = open(r->target, O_RDONLY);
            if (tmp_fd < 0)
                return (1);
            if (fd_in != -1)
                close(fd_in);
            fd_in = tmp_fd;
        }
        else if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
        {
            int flags = O_CREAT | O_WRONLY | (r->type == REDIR_APPEND ? O_APPEND : O_TRUNC);
            int tmp_fd = open(r->target, flags, 0644);
            if (tmp_fd < 0)
                return (1);
            if (fd_out != -1)
                close(fd_out);
            fd_out = tmp_fd;
        }
        r = r->next;
    }
    if (first_heredoc_fd != -1)
    {
        if (dup2(first_heredoc_fd, STDIN_FILENO) == -1)
        {
            close(first_heredoc_fd);
            return (1);
        }
        close(first_heredoc_fd);
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


int ft_exec_create_heredoc(char *delim)
{
    int     hd[2];
    pid_t   pid;
    int     st;

    if (pipe(hd) == -1)
        return (perror("heredoc pipe"), -1);
    pid = fork();
    if (pid == -1)
        return (perror("heredoc fork"), close(hd[0]), close(hd[1]), -1);
    if (pid == 0)
    {
        char    *l;
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


int ft_exec_is_directory(char *p)
{
    struct stat st;

    if (stat(p, &st) == 0 && S_ISDIR(st.st_mode))
        return (1);
    return (0);
}

char    *ft_exec_find_cmd(char *s, t_envp *l)
{
    char    *v;
    char    **dirs;
    char    *full_path;
    int     i;

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
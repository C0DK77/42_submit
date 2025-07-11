/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:11 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/09 15:25:26 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_exec(t_parsing *p, t_envp *envp)
{
	int		fd[2];
	pid_t	pid;

	while (p)
	{
		setup_redirections(p);
		if (p->sep == SEP_PIPE)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (p->sep == SEP_PIPE)
				dup2(fd[1], STDOUT_FILENO);
			exec_cmd(p->line, envp);
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

char	**env_list_to_array(t_envp *envp)
{
	int		count;
	t_envp	*tmp;
	char	**env;
	char	*entry;

	count = 0;
	tmp = envp;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	tmp = envp;
	count = 0;
	while (tmp)
	{
		entry = ft_strjoin(tmp->var, "=");
		env[count] = ft_strjoin(entry, tmp->value);
		free(entry);
		count++;
		tmp = tmp->next;
	}
	env[count] = NULL;
	return (env);
}

char	*find_cmd_path(char *cmd, t_envp *envp)
{
	char	**paths;
	char	*path_var;
	char	*candidate;
	int		i;

	path_var = ft_search_value(envp, "PATH");
	i = 0;
	if (!path_var || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	while (paths && paths[i])
	{
		candidate = ft_strjoin(paths[i], "/");
		candidate = ft_strjoin_free(candidate, cmd);
		if (access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

void	exec_cmd(char **cmd, t_envp *envp)
{
	char	*path;
	char	**env_array;

	if (!cmd || !cmd[0])
		exit(0);
	path = find_cmd_path(cmd[0], envp);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		exit(127);
	}
	env_array = env_list_to_array(envp);
	execve(path, cmd, env_array);
	perror("execve");
	exit(1);
}

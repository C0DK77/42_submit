/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/16 19:00:33 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_exec_builtin(char **s, t_envp **l)
{
	if (!s || !s[0])
		return (0);
	if (ft_strcmp(s[0], "cd") == 0)
	{
		g_exit_status = ft_cd(s, *l);
		return (1);
	}
	else if (ft_strcmp(s[0], "exit") == 0)
	{
		ft_exit(s);
		return (1);
	}
	else if (ft_strcmp(s[0], "echo") == 0)
	{
		g_exit_status = ft_echo(s);
		return (1);
	}
	else if (ft_strcmp(s[0], "pwd") == 0)
	{
		g_exit_status = ft_pwd();
		return (1);
	}
	else if (ft_strcmp(s[0], "env") == 0)
	{
		g_exit_status = ft_env(*l);
		return (1);
	}
	else if (ft_strcmp(s[0], "export") == 0)
	{
		g_exit_status = ft_export(s, l);
		return (1);
	}
	else if (ft_strcmp(s[0], "unset") == 0)
	{
		g_exit_status = ft_unset(s, l);
		return (1);
	}
	return (0);
}

int	ft_exit(char **args)
{
	long long	code;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!ft_is_numeric(args[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			args[1]);
		exit(255);
	}
	if (args[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	code = ft_atoll(args[1]);
	exit(code % 256);
}

int	ft_env(t_envp *l)
{
	while (l)
	{
		if (l->value)
			printf("%s=%s\n", l->var, l->value);
		l = l->next;
	}
	g_exit_status = 0;
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: pwd");
		g_exit_status = 1;
		return (1);
	}
	printf("%s\n", cwd);
	g_exit_status = 0;
	return (0);
}

int	ft_echo(char **s)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (s[1] && ft_strcmp(s[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (s[i])
	{
		printf("%s", s[i]);
		if (s[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_exit_status = 0;
	return (0);
}

int	ft_unset(char **s, t_envp **l)
{
	int		i;
	t_envp	*prev;
	t_envp	*t;

	i = 1;
	while (s[i])
	{
		t = *l;
		prev = NULL;
		while (t)
		{
			if (ft_strcmp(t->var, s[i]) == 0)
			{
				if (prev)
					prev->next = t->next;
				else
					*l = t->next;
				free(t->var);
				free(t->value);
				free(t);
				break ;
			}
			prev = t;
			t = t->next;
		}
		i++;
	}
	g_exit_status = 0;
	return (0);
}

int	ft_export(char **s, t_envp **l)
{
	int		i;
	char	**split;

	i = 1;
	if (!s[1])
	{
		ft_env_sorted(*l);
		g_exit_status = 0;
		return (0);
	}
	while (s[i])
	{
		if (ft_strchr(s[i], '='))
		{
			split = ft_split(s[i], '=');
			ft_setenv(l, split[0], split[1] ? split[1] : "");
			ft_free_split(split);
		}
		else
		{
			if (!ft_env_search_value(*l, s[i]))
				ft_setenv(l, s[i], "");
		}
		i++;
	}
	g_exit_status = 0;
	return (0);
}

int	ft_cd(char **s, t_envp *l)
{
	if (!s[1])
		return (chdir(ft_env_search_value(l, "HOME")));
	if (s[1] && s[2])
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	if (chdir(s[1]) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = 0;
	return (0);
}
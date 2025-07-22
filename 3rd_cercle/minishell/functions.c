/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/22 14:50:06 by corentindes      ###   ########.fr       */
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
		g_exit_status = ft_pwd(s);
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
	else if (ft_strcmp(s[0], ":") == 0)
	{
		g_exit_status = 0;
		return (1);
	}
	return (0);
}

int	ft_exit(char **s)
{
	long long	code;

	printf("exit\n");
	if (!s[1])
		exit(0);
	if (!ft_is_numeric(s[1]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			s[1]);
		exit(255);
	}
	if (s[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	code = ft_atoll(s[1]);
	exit(code % 256);
}

int	ft_env(t_envp *l)
{
	while (l)
	{
		if (l->export && l->value)
			printf("%s=%s\n", l->var, l->value);
		l = l->next;
	}
	g_exit_status = 0;
	return (0);
}

int	ft_pwd(char **s)
{
	char	cwd[PATH_MAX];
	char	*pwd_env;
	int		a;

	a = 0;
	for (int i = 1; s[i]; i++)
	{
		if (s[i][0] == '-')
		{
			if (!ft_strcmp(s[i], "-P"))
				a = 1;
			else if (!ft_strcmp(s[i], "-L"))
				a = 0;
			else
			{
				fprintf(stderr, "minishell: pwd: %s: invalid option\n", s[i]);
				fprintf(stderr, "usage: pwd [-L | -P]\n");
				g_exit_status = 1;
				return (1);
			}
		}
		else
			break ;
	}
	if (a)
	{
		if (!getcwd(cwd, sizeof(cwd)))
		{
			perror("minishell: pwd");
			g_exit_status = 1;
			return (1);
		}
		printf("%s\n", cwd);
	}
	else
	{
		pwd_env = getenv("PWD");
		if (!pwd_env || !pwd_env[0])
		{
			if (!getcwd(cwd, sizeof(cwd)))
			{
				perror("minishell: pwd");
				g_exit_status = 1;
				return (1);
			}
			printf("%s\n", cwd);
		}
		else
			printf("%s\n", pwd_env);
	}
	g_exit_status = 0;
	return (0);
}

int	ft_echo(char **s)
{
	int	i;
	int	l;
	int	j;

	i = 1;
	l = 1;
	while (s[i] && s[i][0] == '-' && s[i][1] == 'n')
	{
		j = 2;
		while (s[i][j] == 'n')
			j++;
		if (s[i][j] != '\0')
			break ;
		l = 0;
		i++;
	}
	while (s[i])
	{
		printf("%s", s[i]);
		if (s[i + 1])
			printf(" ");
		i++;
	}
	if (l)
		printf("\n");
	fflush(stdout);
	g_exit_status = 0;
	return (0);
}

int	ft_unset(char **s, t_envp **l)
{
	int		i;
	t_envp	*t;
	t_envp	*prev;

	i = 1;
	while (s[i])
	{
		t = *l;
		prev = NULL;
		while (t)
		{
			if (strcmp(t->var, s[i]) == 0)
			{
				if (prev)
					prev->next = t->next;
				else
					*l = t->next;
				free(t->var);
				if (t->value)
					free(t->value);
				free(t);
				break ;
			}
			prev = t;
			t = t->next;
		}
		i++;
	}
	return (0);
}

int	ft_export(char **s, t_envp **l)
{
	int		i;
	t_envp	*t;
	char	*eq;
	int		len;
	char	*name;
	char	*v;

	i = 1;
	if (!s[1])
	{
		t = *l;
		while (t)
		{
			if (t->export)
			{
				if (t->value)
					printf("declare -x %s=\"%s\"\n", t->var, t->value);
				else
					printf("declare -x %s\n", t->var);
			}
			t = t->next;
		}
		return (0);
	}
	while (s[i])
	{
		eq = ft_strchr(s[i], '=');
		if (eq)
		{
			len = eq - s[i];
			name = ft_strndup(s[i], len);
			v = ft_strdup(eq + 1);
			ft_env_set(l, name, v, 1);
			free(name);
			free(v);
		}
		else
			ft_env_set(l, s[i], NULL, 1);
		i++;
	}
	return (0);
}

int	ft_cd(char **s, t_envp *l)
{
	char	cwd[PATH_MAX];
	char	*d;
	char	*p;

	if (getcwd(cwd, sizeof(cwd)))
		p = ft_strdup(cwd);
	else
		p = NULL;
	if (!s[1])
		d = ft_env_search_value(l, "HOME");
	else if (s[2])
	{
		fprintf(stderr, "minishell: cd: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	else
		d = s[1];
	if (chdir(d) != 0)
	{
		perror("minishell: cd");
		free(p);
		g_exit_status = 1;
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_env_set(&l, "PWD", cwd, 1);
		if (p)
			ft_env_set(&l, "OLDPWD", p, 1);
	}
	free(p);
	g_exit_status = 0;
	return (0);
}

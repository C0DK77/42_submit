/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 16:03:15 by corentindes      ###   ########.fr       */
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
		g_exit_status = ft_pwd(s, *l);
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
	else if (ft_strcmp(s[0], "history") == 0)
	{
		ft_history_print(g_history);
		return (1);
	}
	return (0);
}

int	ft_exit(char **s)
{
	long long	c;

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
	c = ft_atoll(s[1]);
	exit(c % 256);
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

int	parse_pwd_opts(char **s, int *p)
{
	int	i;
	int	j;

	i = 1;
	*p = 0;
	while (s[i])
	{
		if (s[i][0] != '-' || s[i][1] == '\0')
			break ;
		if (!ft_strcmp(s[i], "--"))
		{
			i++;
			break ;
		}
		j = 1;
		while (s[i][j])
		{
			if (s[i][j] == 'P')
				*p = 1;
			else if (s[i][j] == 'L')
				*p = 0;
			else
			{
				fprintf(stderr, "minishell: pwd: -%c: invalid option\n",
					s[i][j]);
				fprintf(stderr, "usage: pwd [-L | -P]\n");
				g_exit_status = 2;
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_pwd(char **s, t_envp *l)
{
	int		i;
	int		n;
	char	b[PATH_MAX];
	char	*pwd;

	pwd = ft_env_search_value(l, "PWD");
	n = parse_pwd_opts(s, &i);
	if (n < 0)
		return (1);
	if (i)
	{
		if (!getcwd(b, sizeof(b)))
		{
			perror("minishell: pwd");
			g_exit_status = 1;
			return (1);
		}
		printf("%s\n", b);
	}
	else
	{
		if (pwd && *pwd)
			printf("%s\n", pwd);
		else
		{
			if (!getcwd(b, sizeof(b)))
			{
				perror("minishell: pwd");
				g_exit_status = 1;
				return (1);
			}
			printf("%s\n", b);
		}
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
	t_envp	*p;

	i = 1;
	while (s[i])
	{
		t = *l;
		p = NULL;
		while (t)
		{
			if (strcmp(t->var, s[i]) == 0)
			{
				if (p)
					p->next = t->next;
				else
					*l = t->next;
				free(t->var);
				if (t->value)
					free(t->value);
				free(t);
				break ;
			}
			p = t;
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

void	update_pwd_vars(t_envp *l, char *s)
{
	char	c[PATH_MAX];

	if (s)
		ft_env_set(&l, "OLDPWD", s, 1);
	if (getcwd(c, sizeof(c)))
		ft_env_set(&l, "PWD", c, 1);
}

int	ft_cd(char **s, t_envp *l)
{
	int		i;
	char	*target;
	char	*pwd_before;

	target = NULL;
	pwd_before = ft_env_search_value(l, "PWD");
	i = 0;
	while (s[i])
		i++;
	if (i == 1)
	{
		target = ft_env_search_value(l, "HOME");
		if (!target)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			g_exit_status = 1;
			return (1);
		}
	}
	else
	{
		if (ft_strcmp(s[1], "-") == 0)
		{
			target = ft_env_search_value(l, "OLDPWD");
			if (!target)
			{
				fprintf(stderr, "minishell: cd: OLDPWD not set\n");
				g_exit_status = 1;
				return (1);
			}
			printf("%s\n", target);
		}
		else if (ft_strcmp(s[1], "--") == 0)
		{
			if (i == 2)
			{
				target = ft_env_search_value(l, "HOME");
				if (!target)
				{
					fprintf(stderr, "minishell: cd: HOME not set\n");
					g_exit_status = 1;
					return (1);
				}
			}
			else if (i == 3)
				target = s[2];
			else
			{
				fprintf(stderr, "minishell: cd: too many arguments\n");
				g_exit_status = 1;
				return (1);
			}
		}
		else if (s[1][0] == '-' && s[1][1] != '\0')
		{
			fprintf(stderr, "minishell: cd: %s: invalid option\n", s[1]);
			fprintf(stderr, "cd: usage: cd [dir]\n");
			g_exit_status = 2;
			return (1);
		}
		else
		{
			if (i > 2)
			{
				fprintf(stderr, "minishell: cd: too many arguments\n");
				g_exit_status = 1;
				return (1);
			}
			target = s[1];
		}
	}
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		g_exit_status = 1;
		return (1);
	}
	update_pwd_vars(l, pwd_before);
	g_exit_status = 0;
	return (0);
}

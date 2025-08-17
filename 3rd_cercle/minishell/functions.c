/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/17 16:25:31 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_history_add(t_history **h, const char *s)
{
	t_history	*n;
	t_history	*t;

	n = malloc(sizeof(t_history));
	if (!n)
		return ;
	n->line = ft_strdup(s);
	if (!n->line)
	{
		free(n);
		return ;
	}
	n->next = NULL;
	if (!*h)
		*h = n;
	else
	{
		t = *h;
		while (t->next)
			t = t->next;
		t->next = n;
	}
}

void	ft_history_print(t_history *h)
{
	int	i;

	i = 1;
	while (h)
	{
		printf("%5d  %s\n", i, h->line);
		h = h->next;
		i++;
	}
}

void	ft_history_clear(t_history **h)
{
	t_history	*t;

	while (*h)
	{
		t = (*h)->next;
		free((*h)->line);
		free(*h);
		*h = t;
	}
}

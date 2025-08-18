/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/18 22:45:05 by corentindes      ###   ########.fr       */
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

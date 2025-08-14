/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:32:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/14 17:47:51 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	g_var[] = {{"PATH"}, {"PWD"}, {"SHLVL"}, {"HOME"}, {"TERM"}, {"OLDPWD"},
		{NULL}};

int	ft_vars_check(t_envp **l)
{
	int	i;

	i = 0;
	while (g_var[i].var)
	{
		if (!ft_var_check(l, g_var[i].var))
		{
			printf("Init problem %s.\n", g_var[i].var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_var_check(t_envp **l, char *v)
{
	t_envp	*t;
	char	c[PATH_MAX];

	t = ft_env_search_node(*l, v);
	if (t && ft_strcmp(v, "SHLVL") == 0 && !ft_var_shlvl(t))
		return (0);
	if (t)
		return (1);
	if (ft_strcmp(v, "PWD") == 0 && !getcwd(c, sizeof(c)))
	{
		perror("getcwd");
		return (0);
	}
	t = malloc(sizeof(t_envp));
	if (!t)
		return (0);
	if (!ft_var_init(l, t, v))
		return (0);
	return (1);
}

int	ft_var_init(t_envp **l, t_envp *t, char *v)
{
	char	cwd[PATH_MAX];

	t->var = ft_strdup(v);
	if (ft_strcmp(v, "TERM") == 0)
		t->value = ft_strdup("xterm");
	else if (ft_strcmp(v, "HOME") == 0)
		t->value = ft_strdup("/");
	else if (ft_strcmp(v, "PATH") == 0)
		t->value = ft_strdup("/usr/local/bin:/usr/bin:/bin");
	else if (ft_strcmp(v, "OLDPWD") == 0)
		t->value = ft_strdup("");
	else if (ft_strcmp(v, "SHLVL") == 0)
		t->value = ft_strdup("1");
	else if (ft_strcmp(v, "PWD") == 0)
	{
		if (!getcwd(cwd, sizeof(cwd)))
		{
			perror("getcwd");
			free(t->var);
			free(t);
			return (0);
		}
		t->value = ft_strdup(cwd);
	}
	if (!t->var || !t->value)
	{
		free(t->var);
		free(t->value);
		free(t);
		return (0);
	}
	t->next = *l;
	*l = t;
	return (1);
}

int	ft_var_shlvl(t_envp *l)
{
	char	*t;
	int		s;

	s = ft_atoi(l->value);
	s++;
	t = ft_itoa(s);
	if (!t)
		return (0);
	free(l->value);
	l->value = t;
	return (1);
}

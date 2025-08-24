/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:32:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/24 16:29:14 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_env_vars_init_table(void)
{
	t_var	*tb;

	tb = malloc(sizeof(t_var) * 7);
	if (!tb)
		return (NULL);
	tb[0].var = ft_strdup("PATH");
	tb[1].var = ft_strdup("PWD");
	tb[2].var = ft_strdup("SHLVL");
	tb[3].var = ft_strdup("HOME");
	tb[4].var = ft_strdup("TERM");
	tb[5].var = ft_strdup("OLDPWD");
	tb[6].var = NULL;
	return (tb);
}

int	ft_env_vars_check(t_envp **l)
{
	int		i;
	t_var	*vars;

	i = 0;
	vars = ft_env_vars_init_table();
	while (vars[i].var)
	{
		if (!ft_env_list_var_check(l, vars[i].var))
			return (printf("Init problem %s.\n", vars[i].var), 0);
		i++;
	}
	return (1);
}

int	ft_env_list_var_check(t_envp **l, char *v)
{
	t_envp	*t;
	char	c[PATH_MAX];

	t = ft_env_search_node(*l, v);
	if (t)
	{
		if (ft_strcmp(v, "SHLVL") == 0)
			return (ft_var_increase_shlvl(t));
		return (1);
	}
	if (ft_strcmp(v, "PWD") == 0 && !getcwd(c, sizeof(c)))
		return (perror("getcwd"), 0);
	t = malloc(sizeof(t_envp));
	if (!t)
		return (0);
	if (!ft_env_vars_create(l, t, v))
		return (free(t), 0);
	return (1);
}

int	ft_env_vars_create(t_envp **l, t_envp *t, char *v)
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
		t->value = ft_strdup("2");
	else if (ft_strcmp(v, "PWD") == 0)
	{
		if (!getcwd(cwd, sizeof(cwd)))
			return (perror("getcwd"), ft_free_all(2, t->var, t), 0);
		t->value = ft_strdup(cwd);
	}
	if (!t->var || !t->value)
		return (ft_free_all(3, t->var, t->value, t), 0);
	t->export = 1;
	t->next = *l;
	*l = t;
	return (1);
}

int	ft_var_increase_shlvl(t_envp *l)
{
	char	*t;

	t = ft_itoa(ft_atoi(l->value) + 1);
	if (!t)
		return (0);
	free(l->value);
	l->value = t;
	return (1);
}

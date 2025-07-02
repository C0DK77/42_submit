/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:32:26 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/02 16:15:35 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_all_var(t_envp **envp)
{
	int	i;

	i = 0;
	while (g_vars_to_check[i].var)
	{
		if (!check_var(envp, g_vars_to_check[i].var))
		{
			printf("Probleme sur l'initialisation de la variable %s.\n",
				g_vars_to_check[i].var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_check_var(t_envp **envp, char *var)
{
	t_envp	*t;
	char	cwd[PATH_MAX];

	t = ft_search_var(*envp, var);
	if (t && strcmp(var, "SHLVL") == 0 && !shlvl(t))
		return (0);
	if (t)
		return (1);
	if (strcmp(var, "PWD") == 0 && !getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (0);
	}
	t = malloc(sizeof(t_envp));
	if (!t)
		return (0);
	if (!ft_change_var(*envp, t, var))
		return (0);
	return (1);
}

int	ft_change_var(t_envp **envp, t_envp *t, char *var)
{
	char	cwd[PATH_MAX];

	t->var = ft_strdup(var);
	if (strcmp(var, "TERM") == 0)
		t->value = ft_strdup("xterm");
	else if (strcmp(var, "HOME") == 0)
		t->value = ft_strdup("/");
	else if (strcmp(var, "PATH") == 0)
		t->value = ft_strdup("/usr/local/bin:/usr/bin:/bin");
	else if (strcmp(var, "OLDPWD") == 0)
		t->value = ft_strdup("");
	else if (strcmp(var, "SHLVL") == 0)
		t->value = ft_strdup("1");
	else if (strcmp(var, "PWD") == 0)
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
	t->next = *envp;
	*envp = t;
	return (1);
}

int	shlvl(t_envp *t)
{
	char	*t;
	int		s;

	s = ft_atoi(t->value);
	s++;
	t = ft_itoa(s);
	if (!t)
		return (0);
	free(t->value);
	t->value = t;
	return (1);
}

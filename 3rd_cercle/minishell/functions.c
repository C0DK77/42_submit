/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/17 17:33:43 by ecid             ###   ########.fr       */
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

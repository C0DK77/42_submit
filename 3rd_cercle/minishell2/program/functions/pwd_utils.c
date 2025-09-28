/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:03 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/28 23:50:49 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_update_existing(t_envp *e, const char *v, int export_it)
{
	char	*new_val;

	if (v)
	{
		new_val = ft_strdup(v);
		if (!new_val)
			return ;
		free(e->value);
		e->value = new_val;
	}
	if (export_it)
		e->export = 1;
}

static t_envp	*env_new_pair(const char *name, const char *val, int export_it)
{
	t_envp	*n;

	n = malloc(sizeof(t_envp));
	if (!n)
		return (NULL);
	n->var = ft_strdup(name);
	if (val)
		n->value = ft_strdup(val);
	else
		n->value = NULL;
	if (!n->var || (val && !n->value))
	{
		ft_free_all(3, n->var, n->value, n);
		return (NULL);
	}
	if (export_it)
		n->export = 1;
	else
		n->export = 0;
	n->next = NULL;
	return (n);
}

static void	env_append(t_envp **l, t_envp *n)
{
	t_envp	*e;

	if (!*l)
	{
		*l = n;
		return ;
	}
	e = *l;
	while (e->next)
		e = e->next;
	e->next = n;
}

void	update_pwd_vars(t_envp *l, char *s)
{
	char	c[PATH_MAX];

	if (s)
		ft_pwd_export_env_set(&l, "OLDPWD", s, 1);
	if (getcwd(c, sizeof(c)))
		ft_pwd_export_env_set(&l, "PWD", c, 1);
}

void	ft_pwd_export_env_set(t_envp **l, char *s, char *v, int i)
{
	t_envp	*e;
	t_envp	*n;

	if (!l || !s)
		return ;
	e = ft_env_search_node(*l, s);
	if (e)
	{
		env_update_existing(e, v, i);
		return ;
	}
	n = env_new_pair(s, v, i);
	if (!n)
		return ;
	env_append(l, n);
}

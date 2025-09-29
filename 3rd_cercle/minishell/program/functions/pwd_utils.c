/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:03 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 07:17:34 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_pwd_update_vars(t_envp *l, char *s)
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
		ft_env_update_existing(e, v, i);
		return ;
	}
	n = ft_env_new_pair(s, v, i);
	if (!n)
		return ;
	ft_env_append(l, n);
}

void	ft_env_update_existing(t_envp *e, char *v, int i)
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
	if (i)
		e->export = 1;
}

t_envp	*ft_env_new_pair(char *name, char *val, int i)
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
	if (i)
		n->export = 1;
	else
		n->export = 0;
	n->next = NULL;
	return (n);
}

void	ft_env_append(t_envp **l, t_envp *n)
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

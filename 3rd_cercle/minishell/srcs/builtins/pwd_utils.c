/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:03 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/06 17:10:06 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*new_val;

	if (!l || !s)
		return ;
	e = ft_env_search_node(*l, s);
	if (e)
	{
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
		return ;
	}
	n = malloc(sizeof(t_envp));
	if (!n)
		return ;
	n->var = ft_strdup(s);
	if (v)
		n->value = ft_strdup(v);
	else
		n->value = NULL;
	if (!n->var || (v && !n->value))
	{
		ft_free_all(3, n->var, n->value, n);
		return ;
	}
	if (i)
		n->export = 1;
	else
		n->export = 0;
	n->next = NULL;
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

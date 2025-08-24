/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:03 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/24 13:09:39 by ecid             ###   ########.fr       */
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
	t_envp	*n;

	if (ft_env_add_value(l, s, v, i))
		return ;
	n = malloc(sizeof(t_envp));
	n->var = ft_strdup(s);
	if (v)
		n->value = ft_strdup(v);
	else
		NULL;
	n->export = i;
	n->next = (*l)->next;
	(*l)->next = n;
}

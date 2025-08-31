/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:12:03 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/31 18:31:07 by elisacid         ###   ########.fr       */
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

	if (ft_env_add_value(l, s, v, i) == 0)
		return;

	n = (t_envp *)calloc(1, sizeof(t_envp));
	if (!n)
		return;
	n->var = ft_strdup(s);
	if (!n->var)
	{
		free(n);
		return;
	}
	if (v)
	{
		n->value = ft_strdup(v);
		if (!n->value)
		{
			free(n->var);
			free(n);
			return;
		}
	}
	else
		n->value = NULL;
	n->export = (i ? 1 : 0);
	n->next = *l;
	*l = n;
}

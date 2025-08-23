/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:51:22 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/23 10:57:56 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

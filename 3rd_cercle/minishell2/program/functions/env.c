/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:48:05 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/28 23:42:23 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_envp *l)
{
	while (l)
	{
		if (l->export)
		{
			if (l->value && l->value[0] != 0)
			{
				printf("%s=", l->var);
				if (l->value)
					printf("%s", l->value);
				printf("\n");
			}
		}
		l = l->next;
	}
	g_exit_status = 0;
	return (0);
}

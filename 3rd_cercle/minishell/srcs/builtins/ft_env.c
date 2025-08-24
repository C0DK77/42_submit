/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:14:21 by ecid              #+#    #+#             */
/*   Updated: 2025/08/23 20:24:31 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_envp *l)
{
	while (l)
	{
		if (l->export)
		{
			printf("%s=", l->var);
			if (l->value)
				printf("%s", l->value);
			printf("\n");
		}
		l = l->next;
	}
	g_exit_status = 0;
	return (0);
}

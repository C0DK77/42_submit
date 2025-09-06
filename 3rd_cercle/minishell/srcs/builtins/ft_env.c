/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:14:21 by ecid              #+#    #+#             */
/*   Updated: 2025/09/06 18:05:04 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_envp *l)
{
	while (l)
	{
		if (l->export && l->value != NULL)
			printf("%s=%s\n", l->var, l->value);
		l = l->next;
	}
	g_exit_status = 0;
	return (0);
}


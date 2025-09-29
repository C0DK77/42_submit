/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:48:05 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/29 05:40:48 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_env(t_envp *l)
{
	while (l)
	{
		if (l->value)
			printf("%s=%s\n", l->var, l->value);
		l = l->next;
	}
	g_exit_status = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:47:17 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/26 15:10:07 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_exit(char **s)
{
	long long	c;

	printf("exit\n");
	if (!s[1])
		exit(0);
	if (!ft_is_numeric(s[1]))
	{
		ft_putall_fd(2, 3, "minishell: exit: ", s[1],
			": argument numérique nécessaire\n");
		exit(2);
	}
	if (s[2])
	{
		g_exit_status = 1;
		return (ft_putstr_fd("minishell: exit: trop d'arguments\n", 2), 1);
	}
	c = ft_atoll(s[1]);
	exit(c % 256);
}

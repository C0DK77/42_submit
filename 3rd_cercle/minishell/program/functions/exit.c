/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:47:17 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 19:07:25 by corentindes      ###   ########.fr       */
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
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (s[2])
	{
		g_exit_status = 1;
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	}
	c = ft_atoll(s[1]);
	exit(c % 256);
}

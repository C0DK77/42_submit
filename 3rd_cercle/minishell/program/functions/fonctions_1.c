/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:20:27 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 19:20:40 by corentindes      ###   ########.fr       */
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
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n",
			s[1]);
		exit(255);
	}
	if (s[2])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	c = ft_atoll(s[1]);
	exit(c % 256);
}
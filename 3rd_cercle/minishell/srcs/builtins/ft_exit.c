/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:47:15 by ecid              #+#    #+#             */
/*   Updated: 2025/09/02 20:08:21 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_error(char *msg, char *arg)
{
	write(STDERR_FILENO, "minishell: exit: ", ft_strlen("minishell: exit: "));
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
	}
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

int	ft_exit(char **s)
{
	long long	c;

	printf("exit\n");
	if (!s[1])
		exit(0);
	if (!ft_is_numeric(s[1]))
	{
		print_exit_error(": numeric argument required\n", s[1]);
		exit(255);
	}
	if (s[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n",
			ft_strlen("minishell: exit: too many arguments\n"));
		g_exit_status = 1;
		return (1);
	}
	c = ft_atoll(s[1]);
	exit((unsigned char)c);
}

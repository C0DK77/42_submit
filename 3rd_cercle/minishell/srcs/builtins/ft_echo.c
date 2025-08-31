/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:23:32 by ecid              #+#    #+#             */
/*   Updated: 2025/08/31 13:11:30 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i])
		return (0);
	return (1);
}

int	ft_echo(char **s)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (s[i] && ft_echo_option(s[i]))
	{
		n_option = 1;
		i++;
	}
	while (s[i])
	{
		printf("%s", s[i]);
		if (s[i + 1])
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
	g_exit_status = 0;
	return (0);
}

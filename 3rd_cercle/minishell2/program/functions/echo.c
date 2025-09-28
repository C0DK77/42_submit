/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:49:06 by corentindes       #+#    #+#             */
/*   Updated: 2025/09/28 23:41:14 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **s)
{
	int	i;
	int	o;

	i = 1;
	o = 0;
	while (s[i] && ft_echo_option(s[i]))
	{
		o = 1;
		i++;
	}
	while (s[i])
	{
		printf("%s", s[i]);
		if (s[i + 1])
			printf(" ");
		i++;
	}
	if (!o)
		printf("\n");
	g_exit_status = 0;
	return (0);
}

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

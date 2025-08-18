/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 22:49:06 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/18 22:49:16 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_echo(char **s)
{
	int i;
	int l;
	int j;

	i = 1;
	l = 1;
	while (s[i] && s[i][0] == '-' && s[i][1] == 'n')
	{
		j = 2;
		while (s[i][j] == 'n')
			j++;
		if (s[i][j] != '\0')
			break ;
		l = 0;
		i++;
	}
	while (s[i])
	{
		printf("%s", s[i]);
		if (s[i + 1])
			printf(" ");
		i++;
	}
	if (l)
		printf("\n");
	fflush(stdout);
	g_exit_status = 0;
	return (0);
}

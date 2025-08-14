/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_unclosed_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:07:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/04 10:25:57 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_has_unclosed_quote(char *str)
{
	int i;
	int sg;
	int db;
	i = 0;
	sg = 0;
	db = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sg++;
		if (str[i] == '\"')
			db++;
		i++;
	}
	if (sg % 2 != 0 || db % 2 != 0)
		return (1);
	return (0);
}
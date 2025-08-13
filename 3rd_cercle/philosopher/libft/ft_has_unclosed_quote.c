/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_unclosed_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:07:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/13 16:00:18 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_has_unclosed_quote(char *s)
{
	int	i;
	int	sg;
	int	db;

	i = 0;
	sg = 0;
	db = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			sg++;
		if (s[i] == '\"')
			db++;
		i++;
	}
	if (sg % 2 != 0 || db % 2 != 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_unclosed_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:07:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/14 16:49:20 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_has_unclosed_quote(char *s)
{
	int	sg;
	int	db;

	sg = 0;
	db = 0;
	while (*s)
	{
		if (*s == '\'')
			sg++;
		if (*s == '\"')
			db++;
		s++;
	}
	if (sg % 2 != 0 || db % 2 != 0)
		return (1);
	return (0);
}

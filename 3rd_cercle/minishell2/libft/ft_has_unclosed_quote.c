/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_has_unclosed_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:07:18 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/22 17:36:54 by corentindes      ###   ########.fr       */
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
		if (*s == '\'' && db == 0)
			sg = !sg;
		else if (*s == '\"' && sg == 0)
			db = !db;
		s++;
	}
	return (sg || db);
}

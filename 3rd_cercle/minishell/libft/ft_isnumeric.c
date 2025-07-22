/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:52:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/22 09:56:14 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_is_numeric(char *s)
{
	int				i;
	unsigned long	res;
	int				sign;

	i = 0;
	res = 0;
	sign = 1;
	if (s[0] == '-')
		sign = -1;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		if (res > (unsigned long)(LONG_MAX / 10)
			|| (res == (unsigned long)(LONG_MAX / 10) && (s[i]
					- '0') > (sign == 1 ? LONG_MAX % 10 : -(LONG_MIN % 10))))
			return (0);
		res = (res * 10) + (s[i] - 48);
		i++;
	}
	return (1);
}

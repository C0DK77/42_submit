/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:52:44 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/13 18:22:18 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_is_numeric(char *s)
{
	unsigned long	res;
	int				sign;
	long			limit;

	res = 0;
	sign = 1;
	limit = -(LONG_MIN % 10);
	if (*s == '-')
		sign = -1;
	while (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (sign == 1)
			limit = LONG_MAX % 10;
		if (!ft_isdigit(*s) || res > (unsigned long)(LONG_MAX / 10)
			|| (res == (unsigned long)(LONG_MAX / 10) && (*s - '0') > limit))
			return (0);
		res = (res * 10) + (*s - 48);
		s++;
	}
	return (1);
}

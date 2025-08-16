/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:44:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/13 16:00:29 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *s)
{
	long long int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (isspace(*s))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (isdigit(*s))
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (sign * res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:10:25 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/14 16:47:10 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		sign = -1;
	while (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (sign * res);
}

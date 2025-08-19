/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:40:36 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/16 13:29:25 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t	ft_atoi64(char *s)
{
	int64_t	res;
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
		res = (res * 10) + (*s - '0');
		s++;
	}
	return (res * sign);
}

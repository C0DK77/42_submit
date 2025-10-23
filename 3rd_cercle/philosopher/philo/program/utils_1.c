/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 04:08:01 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 05:50:14 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_av(int ac, char **av)
{
	int	i;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (0);
	if (ft_atoi64(av[1]) < 1 || ft_atoi64(av[1]) > 200)
	{
		printf("Number of philosophers must be\n");
		printf("  1 <= Philosophers <= 200\n");
		return (0);
	}
	while (i < ac)
	{
		if (ft_atoi64(av[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (7 <= c && c <= 13))
		return (1);
	return (0);
}

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

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (1);
	return (0);
}

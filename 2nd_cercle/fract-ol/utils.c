/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 01:57:58 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/10 03:20:41 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

int	ft_is_in_plan(double x, double y, int i, t_fractal *f)
{
	return (x * x + y * y <= 4 && i < f->max);
}

double	ft_parse_digits(const char **ps, int *e)
{
	int		i;
	double	res;

	res = 0.0;
	*e = 0;
	i = **ps;
	while (i != '\0' && ft_isdigit(i))
	{
		res = res * 10.0 + (i - '0');
		(*ps)++;
		i = **ps;
	}
	if (**ps == '.')
	{
		(*ps)++;
		i = **ps;
		while (i != '\0' && ft_isdigit(i))
		{
			res = res * 10.0 + (i - '0');
			*e -= 1;
			(*ps)++;
			i = **ps;
		}
	}
	return (res);
}

double	ft_atoi_double(const char *s)
{
	int		i;
	double	res;
	int		sign;

	sign = 1;
	if (!s)
		return (0.0);
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	res = ft_parse_digits(&s, &i);
	return (sign * res * ft_power(10.0, i));
}

int	ft_power(int n, int i)
{
	int	res;

	res = 1;
	while (i > 0)
	{
		if (i % 2 == 1)
			res *= n;
		n *= n;
		i /= 2;
	}
	return (res);
}

double	ft_fabs(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

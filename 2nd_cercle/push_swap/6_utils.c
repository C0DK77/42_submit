/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/27 15:06:42 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	ft_list_size(t_ps *p)
{
	int	i;

	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

int	ft_max_min_rank(char *a, t_ps *p)
{
	int	max;
	int	min;

	max = p->rank;
	min = p->rank;
	while (p)
	{
		if (p->rank > max)
			max = p->rank;
		if (p->rank < min)
			min = p->rank;
		p = p->next;
	}
	if (ft_strcmp(a, "max") == 0)
		return (max);
	else if (ft_strcmp(a, "min") == 0)
		return (min);
	return (0);
}

int	ft_get_position(t_ps *p, int target)
{
	int	i;

	i = 0;
	while (p)
	{
		if (p->rank == target)
			return (i);
		p = p->next;
		i++;
	}
	return (-1);
}

long	ft_atoi_long(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}

int	ft_get_chunks(int size)
{
	if (size <= 20)
		return (3);
	else if (size <= 100)
		return (15);
	else if (size <= 200)
		return (25);
	else if (size <= 500)
		return (45);
	return (60);
}

int	ft_get_rank_last_nb(t_ps *p)
{
	if (!p)
	return (0);

	while (p->next)
		p = p->next;
	return (p->rank);
}
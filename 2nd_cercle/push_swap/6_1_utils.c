/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_1_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/07 15:47:06 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	ft_lst_size(t_ps *p)
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

int	ft_rank(char *a, int target, t_ps *p)
{
	int	i;
	int	max;
	int	min;

	i = 0;
	max = p->rank;
	min = p->rank;
	while (p)
	{
		if (p->rank == target)
			return (i);
		if (p->rank > max)
			max = p->rank;
		if (p->rank < min)
			min = p->rank;
		p = p->next;
		i++;
	}
	if (ft_strcmp(a, "max") == 0)
		return (max);
	else if (ft_strcmp(a, "min") == 0)
		return (min);
	return (p->rank);
}

int	ft_pos(int rank, t_ps *p)
{
	int	i;
	int	min;
	int	max;

	i = 0;
	min = ft_rank("min", 0, p);
	max = ft_rank("max", 0, p);
	if (rank < min || rank > max)
		return (ft_rank("", max, p) + 1);
	while (p->next)
	{
		if (p->rank < rank && p->next->rank > rank)
			return (i + 1);
		p = p->next;
		i++;
	}
	return (min);
}

long	ft_atoi_long(const char *s)
{
	long	i;
	int		sign;

	i = 0;
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
		i = i * 10 + (*s - '0');
		s++;
	}
	return (i * sign);
}

int	ft_0_patience(t_ps *p)
{
	int	i;

	i = 0;
	while (p)
	{
		if (p->patience == 0)
			return (i);
		p = p->next;
		i++;
	}
	return (-1);
}

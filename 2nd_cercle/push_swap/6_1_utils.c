/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_1_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/03 15:30:23 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (target == -1)
		return (p->rank);
	return (0);
}

int	ft_get_target_pos(t_ps *a, int rank)
{
	int	min;
	int	max;
	int	i;

	i = 0;
	min = ft_max_min_rank("min", a);
	max = ft_max_min_rank("max", a);
	if (ft_list_size(a) == 0)
		return (0);
	if (rank < min || rank > max)
		return (ft_get_position(a, max) + 1);
	while (a->next)
	{
		if (a->rank < rank && a->next->rank > rank)
			return (i + 1);
		a = a->next;
		i++;
	}
	return (ft_get_position(a, min));
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

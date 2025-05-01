/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_1_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/01 15:02:00 by codk             ###   ########.fr       */
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
	if (ft_strcmp(target, "last") == 0)
		return (p->rank);
}

int	ft_get_target_pos(t_ps *a, int rank)
{
	int		pos;
	int		size;
	t_ps	*t;

	pos = 0;
	size = ft_list_size(a);
	t = a;
	if (rank < ft_max_min_rank("min", a))
		return (0);
	if (rank > ft_max_min_rank("max", a))
		return (size);
	while (t && t->next)
	{
		if (t->rank < rank && rank < t->next->rank)
			return (pos + 1);
		t = t->next;
		pos++;
	}
	return (size);
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


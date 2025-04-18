/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:17:50 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/18 20:47:35 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	ft_list_size(t_ps_list *pile)
{
	int	i;

	i = 0;
	while (pile)
	{
		pile = pile->next;
		i++;
	}
	return (i);
}

int	ft_max_min_rank(char *a, t_ps_list *pile)
{
	int	max;
	int	min;

	max = pile->rank;
	min = pile->rank;
	while (pile)
	{
		if (pile->rank > max)
			max = pile->rank;
		if (pile->rank < min)
			min = pile->rank;
		pile = pile->next;
	}
	if (ft_strcmp(a, "max") == 0)
		return (max);
	else if (ft_strcmp(a, "min") == 0)
		return (min);
	return (0);
}

int	ft_get_position(t_ps_list *pile, int target)
{
	int	i;

	i = 0;
	while (pile)
	{
		if (pile->rank == target)
			return (i);
		pile = pile->next;
		i++;
	}
	return (-1);
}

long	ft_atoi_long(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

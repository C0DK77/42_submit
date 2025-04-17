/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/17 19:50:04 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_sort_three(t_ps_list **pile)
{
	int	a;
	int	b;
	int	c;

	a = (*pile)->nb;
	b = (*pile)->next->nb;
	c = (*pile)->next->next->nb;
	if (a > b && b < c && a < c)
		ft_functions('s', 'a', pile);
	else if (a > b && b > c)
	{
		ft_functions('s', 'a', pile);
		ft_functions('r', 'a', pile);
	}
	else if (a > b && b < c && a > c)
		ft_functions('r', 'a', pile);
	else if (a < b && b > c && a < c)
	{
		ft_functions('s', 'a', pile);
		ft_functions('r', 'a', pile);
	}
	else if (a < b && b > c && a > c)
		ft_function_revert('a', pile);
}

void	ft_sort_five(t_ps_list **a, t_ps_list **b)
{
	int	min;
	int	pos;

	while (ft_list_size(*a) > 3)
	{
		min = ft_max_min_rank('n', *a);
		pos = ft_get_position(*a, min);
		if (pos == 0)
			ft_function_push('b', a, b);
		else if (pos == 1)
		{
			ft_functions('s', 'a', a);
			ft_function_push('b', a, b);
		}
		else if (pos == 2)
		{
			ft_functions('r', 'a', a);
			ft_functions('r', 'a', a);
			ft_function_push('b', a, b);
		}
		else if (pos == 3)
		{
			ft_function_revert('a', a);
			ft_function_revert('a', a);
			ft_function_push('b', a, b);
		}
		else if (pos == 4)
		{
			ft_function_revert('a', a);
			ft_function_push('b', a, b);
		}
	}
	ft_sort_three(a);
	if ((*b)->nb < (*b)->next->nb)
		ft_functions('s', 'b', b);
	ft_function_push('a', b, a);
	ft_function_push('a', b, a);
}

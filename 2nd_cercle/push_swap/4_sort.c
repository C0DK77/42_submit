/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/18 12:08:48 by corentindes      ###   ########.fr       */
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
		ft_functions("sa", pile);
	else if (a > b && b > c)
	{
		ft_functions("sa", pile);
		ft_function_revert('a', pile);
	}
	else if (a > b && b < c && a > c)
		ft_functions("ra", pile);
	else if (a < b && b > c && a < c)
	{
		ft_functions("sa", pile);
		ft_functions("ra", pile);
	}
	else if (a < b && b > c && a > c)
		ft_function_revert('a', pile);
}

void	ft_sort_five(int size, t_ps_list **pile_a, t_ps_list **pile_b)
{
	int	i;

	while (ft_list_size(*pile_a) > 3)
	{
		i = ft_get_position(*pile_a, ft_max_min_rank('n', *pile_a));
		if (i == 0)
			ft_function_push('b', pile_a, pile_b);
		else if (i == 1)
		{
			ft_functions("sa", pile_a);
			ft_function_push('b', pile_a, pile_b);
		}
		else if (i == 2)
		{
			ft_functions("ra", pile_a);
			ft_functions("ra", pile_a);
			ft_function_push('b', pile_a, pile_b);
		}
		else if (i == 3)
		{
			ft_function_revert('a', pile_a);
			ft_function_revert('a', pile_a);
			ft_function_push('b', pile_a, pile_b);
		}
		else if (i == 4)
		{
			ft_function_revert('a', pile_a);
			ft_function_push('b', pile_a, pile_b);
		}
	}
	ft_sort_three(pile_a);
	if (*pile_b && (*pile_b)->next && (*pile_b)->nb < (*pile_b)->next->nb)
		ft_functions("sb", pile_b);
	if (size == 5)
	{
		ft_function_push('a', pile_b, pile_a);
		ft_function_push('a', pile_b, pile_a);
	}
	else if (size == 4)
		ft_function_push('a', pile_b, pile_a);
}

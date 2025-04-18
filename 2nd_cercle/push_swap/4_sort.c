/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/18 20:52:22 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_sort(int size, t_ps_list **pile_a, t_ps_list **pile_b,
		t_ps_list_action **list)
{
	if (size == 2)
		ft_functions("sa", pile_a, list);
	else if (size == 3)
		ft_sort_three(pile_a, list);
	else if (size <= 5)
		ft_sort_five(size, pile_a, pile_b, list);
}

void	ft_sort_three(t_ps_list **pile, t_ps_list_action **list)
{
	int	a;
	int	b;
	int	c;

	a = (*pile)->nb;
	b = (*pile)->next->nb;
	c = (*pile)->next->next->nb;
	if (a > b && b < c && a < c)
		ft_functions("sa", pile, list);
	else if (a > b && b > c)
	{
		ft_functions("sa", pile, list);
		ft_function_revert("rra", pile, list);
	}
	else if (a > b && b < c && a > c)
		ft_functions("ra", pile, list);
	else if (a < b && b > c && a < c)
	{
		ft_functions("sa", pile, list);
		ft_functions("ra", pile, list);
	}
	else if (a < b && b > c && a > c)
		ft_function_revert("rra", pile, list);
}

void	ft_sort_five(int size, t_ps_list **pile_a, t_ps_list **pile_b,
		t_ps_list_action **list)
{
	int	i;

	while (ft_list_size(*pile_a) > 3)
	{
		i = ft_get_position(*pile_a, ft_max_min_rank("min", *pile_a));
		if (i == 0)
			ft_function_push("pb", pile_a, pile_b, list);
		else if (i == 1)
		{
			ft_functions("sa", pile_a, list);
			ft_function_push("pb", pile_a, pile_b, list);
		}
		else if (i == 2)
		{
			ft_functions("ra", pile_a, list);
			ft_functions("ra", pile_a, list);
			ft_function_push("pb", pile_a, pile_b, list);
		}
		else if (i == 3)
		{
			ft_function_revert("rra", pile_a, list);
			ft_function_revert("rra", pile_a, list);
			ft_function_push("pb", pile_a, pile_b, list);
		}
		else if (i == 4)
		{
			ft_function_revert("rra", pile_a, list);
			ft_function_push("pb", pile_a, pile_b, list);
		}
	}
	ft_sort_three(pile_a, list);
	if (*pile_b && (*pile_b)->next && (*pile_b)->nb < (*pile_b)->next->nb)
		ft_functions("sb", pile_b, list);
	if (size == 5)
	{
		ft_function_push("pa", pile_b, pile_a, list);
		ft_function_push("pa", pile_b, pile_a, list);
	}
	else if (size == 4)
		ft_function_push("pa", pile_b, pile_a, list);
}

void	ft_sortin_a(int size, t_ps_list **pile_a, t_ps_list **pile_b,
		t_ps_list_action **list)
{
	int	group;

	group = 1;
	while (*pile_a)
	{
		if ((*pile_a)->rank < (size / 5) * group)
		{
			ft_function_push("pb", pile_a, pile_b, list);
			if ((*pile_b)->rank < ((size / 5) * group) - ((size / 5) / 2))
				ft_functions("rb", pile_b, list);
		}
		else
			ft_functions("ra", pile_a, list);
		if (!ft_ispartofgroup(pile_a, size / 5 * group))
			group++;
	}
}

void	ft_sortin_b(int size, t_ps_list **pile_a, t_ps_list **pile_b,
		t_ps_list_action **list)
{
	while (*pile_b)
	{
		if (ft_get_position(*pile_b, ft_max_min_rank("max", *pile_b)) <= size
			/ 2)
		{
			while ((*pile_b)->rank != ft_max_min_rank("max", *pile_b))
				ft_functions("rb", pile_b, list);
		}
		else
		{
			while ((*pile_b)->rank != ft_max_min_rank("max", *pile_b))
				ft_function_revert("rrb", pile_b, list);
		}
		ft_function_push("pa", pile_b, pile_a, list);
	}
}

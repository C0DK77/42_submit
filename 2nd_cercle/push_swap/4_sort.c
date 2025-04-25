/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/24 10:57:17 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	printf("%i", len);
	if (len == 2)
		ft_swap_rotate("sa", 0, p1, p2, l);
	else if (len <= 5)
		ft_sort_until_five(len, p1, p2, l);
	else
	{
		ft_sortin_a(len, p1, p2, l);
		// ft_sortin_b(len, p1, p2, l);
	}
}

void	ft_sort_three(t_ps **p1, t_ps **p2, t_action **l)
{
	int	a;
	int	b;

	a = ft_max_min_rank("min", *p1);
	b = ft_max_min_rank("max", *p1);
	if (ft_get_position(*p1, a) == 0)
	{
		ft_swap_rotate("sa", 0, p1, p2, l);
		ft_swap_rotate("ra", 0, p1, p2, l);
	}
	else if (ft_get_position(*p1, b - 1) == 0 && ft_get_position(*p1, a) == 1)
		ft_swap_rotate("sa", 0, p1, p2, l);
	else if (ft_get_position(*p1, a - 1) == 0 && ft_get_position(*p1, b) == 1)
		ft_reverse("rra", 0, p1, p2, l);
	else if (ft_get_position(*p1, b) == 0 && ft_get_position(*p1, a) == 1)
		ft_swap_rotate("ra", 0, p1, p2, l);
	else if (ft_get_position(*p1, b) == 0 && ft_get_position(*p1, b - 1) == 1)
	{
		printf("\nOK");

		ft_swap_rotate("ra", 0, p1, p2, l);
		ft_swap_rotate("sa", 0, p1, p2, l);
	}
}

void	ft_sort_until_five(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	a;
	int	count;

	count = 0;
	while (len > 3)
	{
		a = ft_max_min_rank("min", *p1);
		if (ft_get_position(*p1, a) == 0)
		{
			ft_push("pb", p2, p1, l);
			len--;
			count++;
		}
		else
			ft_swap_rotate("ra", 0, p1, p2, l);
	}
	ft_sort_three(p1, p2, l);
	while (count--)
		ft_push("pa", p1, p2, l);
	ft_print(p1, p2, l);

}

void	ft_sortin_a(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	group;
	int	pushed;
	int	chunk;

	group = 1;
	pushed = 0;
	chunk = ft_get_chunks(len);
	while (pushed < len)
	{
		if ((*p1)->rank < chunk * group)
		{
			ft_push("pb", p2, p1, l);
			pushed++;
			ft_print(p1, p2, l);
			if ((*p2)->rank < (chunk * group) - (chunk / 2))
				ft_swap_rotate("rb", 0, p2, p1, l);
		}
		else
			ft_swap_rotate("ra", 0, p1, p2, l);
		if (pushed >= group * chunk && group * chunk < len)
			group++;
		printf("%i", pushed);
	}
	ft_print(p1, p2, l);
	// ft_dual_sort(p1, p2, l);
	// ft_print(p1, p2, l);
}

void	ft_sortin_b(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	while (*p2)
	{
		if (ft_get_position(*p2, ft_max_min_rank("max", *p2)) <= len / 2)
		{
			while ((*p2)->rank != ft_max_min_rank("max", *p2))
				ft_swap_rotate("rb", 0, p2, p1, l);
		}
		else
		{
			while ((*p2)->rank != ft_max_min_rank("max", *p2))
				ft_reverse("rrb", 0, p2, p1, l);
		}
		ft_push("pa", p2, p1, l);
	}
}

int	needs_rotate_a(t_ps *a)
{
	// Ex : tu pourrais dire "je rotate A si son top est au mauvais endroit"
	return (a->rank > ft_max_min_rank("min", a));
}

int	needs_reverse_rotate_a(t_ps *a)
{
	// Même idée en inversé
	return (a->rank < ft_max_min_rank("max", a));
}
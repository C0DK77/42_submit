/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/01 14:53:49 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	if (len == 2)
		ft_swap_rotate("sa", 0, p1, p2, l);
	else if (len <= 10)
		ft_sort_ten(len, p1, p2, l);
	else
		ft_sort(len, p1, p2, l);
}

void	ft_sort_three(t_ps **p1, t_ps **p2, t_action **l)
{
	int	a;
	int	b;

	a = ft_max_min_rank("min", *p1);
	b = ft_max_min_rank("max", *p1);
	if (ft_verif_ranking(p1))
		return ;
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
		ft_swap_rotate("ra", 0, p1, p2, l);
		ft_swap_rotate("sa", 0, p1, p2, l);
	}
}

void	ft_sort_ten(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	a;
	int	i;

	i = 0;
	while (len > 3)
	{
		a = ft_max_min_rank("min", *p1);
		if (ft_verif_ranking(p1) && !p2)
			return ;
		if (ft_get_position(*p1, a) == 0)
		{
			ft_push("pb", p2, p1, l);
			len--;
			i++;
		}
		else if (ft_get_position(*p1, a) == 1)
			ft_swap_rotate("sa", 0, p1, p2, l);
		else if (ft_get_position(*p1, a) <= len / 2)
			ft_swap_rotate("ra", 0, p1, p2, l);
		else
			ft_reverse("rra", 0, p1, p2, l);
		ft_print(p1, p2, l);
	}
	ft_sort_three(p1, p2, l);
	while (i--)
		ft_push("pa", p1, p2, l);
}

void	ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	*tab;
	int	len;
	int	*lis;

	tab = ft_create_tab(*p1, len);
	lis = ft_tab_add_patience(tab, len, &len);
	free(tab);
	ft_append_lis(*p1, lis, len);
	free(lis);
	ft_push_b(len, p1, p2, l);
	reinsert_b_greedy(p1, p2, l);
	final_rotate_a(p1, l);
}

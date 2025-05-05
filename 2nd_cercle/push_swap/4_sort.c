/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/05 09:51:33 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	if (len == 2)
		ft_swap_rotate("sa", p1, l);
	else if (len <= 5)
		ft_sort_ten(len, p1, p2, l);
	else
		ft_sort_big(len, p1, p2, l);
}

void	ft_sort_three(t_ps **p, t_action **l)
{
	int	a;
	int	b;

	a = ft_max_min_rank("min", *p);
	b = ft_max_min_rank("max", *p);
	if (ft_verif_ranking(p))
		return ;
	if (ft_get_position(*p, a) == 0)
	{
		ft_swap_rotate("sa", p, l);
		ft_swap_rotate("ra", p, l);
	}
	else if (ft_get_position(*p, b - 1) == 0 && ft_get_position(*p, a) == 1)
		ft_swap_rotate("sa", p, l);
	else if (ft_get_position(*p, a - 1) == 0 && ft_get_position(*p, b) == 1)
		ft_reverse("rra", p, l);
	else if (ft_get_position(*p, b) == 0 && ft_get_position(*p, a) == 1)
		ft_swap_rotate("ra", p, l);
	else if (ft_get_position(*p, b) == 0 && ft_get_position(*p, b - 1) == 1)
	{
		ft_swap_rotate("ra", p, l);
		ft_swap_rotate("sa", p, l);
	}
}

void	ft_sort_ten(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	a;
	int	i;

	i = len - 3;
	while (len > 3)
	{
		a = ft_max_min_rank("min", *p1);
		if (ft_verif_ranking(p1) && !p2)
			return ;
		if (ft_get_position(*p1, a) == 0)
		{
			ft_push("pb", p2, p1, l);
			len--;
		}
		else if (ft_get_position(*p1, a) == 1)
			ft_swap_rotate("sa", p1, l);
		else if (ft_get_position(*p1, a) <= len / 2)
			ft_swap_rotate("ra", p1, l);
		else
			ft_reverse("rra", p1, l);
	}
	ft_sort_three(p1, l);
	while (i--)
		ft_push("pa", p1, p2, l);
}

void	ft_sort_big(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	*tab;
	int	*lis_i;
	int	lis_l;

	tab = ft_create_tab(*p1, len);
	lis_i = ft_tab_add_patience(tab, len, &lis_l);
	free(tab);
	ft_append_patience(*p1, lis_i, lis_l);
	ft_push_b(len, lis_l, p1, p2, l);
	reinsert_b_greedy(p1, p2, l);
	final_rotate_a(p1, l);
	free(lis_i);
}

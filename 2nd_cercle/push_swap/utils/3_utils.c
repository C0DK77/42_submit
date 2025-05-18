/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:11:54 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/18 17:32:17 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_push_a(t_ps **p1, t_ps **p2, int best_i, t_action **l)
{
	int	a;

	if (best_i <= ft_lst_size(*p2) / 2)
		while (best_i-- > 0)
			ft_swap_rotate("rb", p2, l);
	else
	{
		a = ft_lst_size(*p2) - best_i;
		while (a-- > 0)
			ft_reverse("rrb", p2, l);
	}
	printf("\n\nPOS_A : %i\n\n", ft_pos((*p2)->rank, *p1));
	printf("\n\nLAST P1 : %i\n\n", ft_rank("", 0, *p1));
	ft_rotation_a(p1, ft_pos((*p2)->rank, *p1), l);
	ft_push("pa", p1, p2, l);
}

void	ft_rotation_a(t_ps **p1, int pos_a, t_action **l)
{
	t_rotation	rot;

	rot.cnt_ra = 0;
	rot.cnt_rra = 0;
	ft_calcul_rotation(p1, pos_a, &rot);
	ft_apply_rotation(p1, rot, l);
}

void	ft_apply_rotation(t_ps **p1, t_rotation rot, t_action **l)
{
	while (rot.cnt_ra-- > 0)
		ft_swap_rotate("ra", p1, l);
	while (rot.cnt_rra-- > 0)
		ft_reverse("rra", p1, l);
}

void	ft_calcul_rotation(t_ps **p1, int pos_a, t_rotation *rot)
{
	printf("\n\nLIST SIZE : %i\n\n", ft_lst_size(*p1));
	if (pos_a <= ft_lst_size(*p1) / 2)
	{
		rot->cnt_ra = pos_a;
		rot->cnt_rra = 0;
	}
	else
	{
		rot->cnt_ra = 0;
		rot->cnt_rra = ft_lst_size(*p1) - pos_a;
	}
}

int	ft_cost(int len_1, int len_2, int pos_1, int pos_2)
{
	int	a;
	int	cost;

	a = len_2 - pos_2;
	cost = pos_2;
	if (pos_1 > cost)
		cost = pos_1;
	if ((len_1 - pos_1) > a)
		a = (len_1 - pos_1);
	if (a < cost)
		cost = a;
	if (pos_1 + (len_2 - pos_2) < cost)
		cost = pos_1 + (len_2 - pos_2);
	if ((len_1 - pos_1) + pos_2 < cost)
		cost = (len_1 - pos_1) + pos_2;
	return (cost);
}

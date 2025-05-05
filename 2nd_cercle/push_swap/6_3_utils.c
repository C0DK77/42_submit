/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_3_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:11:54 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/05 10:16:40 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	final_rotate_a(t_ps **p, t_action **l)
{
	int	i;
	int	j;

	if (!p || !*p)
		return ;
	i = ft_get_position(*p, ft_max_min_rank("min", *p));
	if (i <= ft_list_size(*p) / 2)
	{
		while (i > 0)
		{
			ft_swap_rotate("ra", p, l);
			i--;
		}
	}
	else
	{
		j = ft_list_size(*p) - i;
		while (j > 0)
		{
			ft_reverse("rra", p, l);
			j--;
		}
	}
}

void	execute_rotations(t_ps **p1, t_ps **p2, int pos_a, int pos_b, int sz_a,
		int sz_b, t_action **l)
{
	int	cnt_ra;
	int	cnt_rra;
	int	cnt_rb;
	int	cnt_rrb;

	cnt_ra = (pos_a <= sz_a / 2) ? pos_a : 0;
	cnt_rra = (pos_a > sz_a / 2) ? sz_a - pos_a : 0;
	cnt_rb = (pos_b <= sz_b / 2) ? pos_b : 0;
	cnt_rrb = (pos_b > sz_b / 2) ? sz_b - pos_b : 0;
	while (cnt_ra > 0 && cnt_rb > 0)
	{
		ft_swap_rotate("ra", p1, l);
		ft_swap_rotate("rb", p2, l);
		cnt_ra--;
		cnt_rb--;
	}
	while (cnt_rra > 0 && cnt_rrb > 0)
	{
		ft_reverse("rra", p1, l);
		ft_reverse("rrb", p2, l);
		cnt_rra--;
		cnt_rrb--;
	}
	while (cnt_ra-- > 0)
		ft_swap_rotate("ra", p1, l);
	while (cnt_rra-- > 0)
		ft_reverse("rra", p1, l);
	while (cnt_rb-- > 0)
		ft_swap_rotate("rb", p2, l);
	while (cnt_rrb-- > 0)
		ft_reverse("rrb", p2, l);
}

int	get_lis_length(int *tab, int len)
{
	int *tail = malloc(sizeof(*tail) * len);
	int lis_end = 0;
	int i = 0;

	while (i < len)
	{
		int x = tab[i];
		int l = 0, r = lis_end;
		while (l < r)
		{
			int m = (l + r) / 2;
			if (tail[m] < x)
				l = m + 1;
			else
				r = m;
		}
		tail[l] = x;
		if (l == lis_end)
			lis_end++;
		i++;
	}

	free(tail);
	return (lis_end);
}
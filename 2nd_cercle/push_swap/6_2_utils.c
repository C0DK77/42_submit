/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_2_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:02 by codk              #+#    #+#             */
/*   Updated: 2025/05/07 16:50:55 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_build_patience(int *tab, int len, int *tail, int *pos, int *prev,
		int *out_lis_len)
{
	int	i;
	int	left;
	int	right;
	int	mid;

	i = 0;
	*out_lis_len = 0;
	while (i < len)
	{
		left = 0;
		right = *out_lis_len;
		while (left < right)
		{
			mid = (left + right) / 2;
			if (tail[mid] < tab[i])
				left = mid + 1;
			else
				right = mid;
		}
		tail[left] = tab[i];
		pos[left] = i;
		prev[i] = -1;
		if (left > 0)
			prev[i] = pos[left - 1];
		if (left + 1 > *out_lis_len)
			*out_lis_len = left + 1;
		i++;
	}
}

int	*ft_tab_add_patience(int *tab, int len, int *out_lis_len)
{
	int	*tail;
	int	*pos;
	int	*prev;
	int	*lis_idx;
	int	k;
	int	i;

	tail = malloc(sizeof *tail * len);
	pos = malloc(sizeof *pos * len);
	prev = malloc(sizeof *prev * len);
	ft_build_patience(tab, len, tail, pos, prev, out_lis_len);
	lis_idx = malloc(sizeof *lis_idx * (*out_lis_len));
	k = pos[*out_lis_len - 1];
	i = *out_lis_len - 1;
	while (i >= 0)
	{
		lis_idx[i] = k;
		k = prev[k];
		i--;
	}
	free(tail);
	free(pos);
	free(prev);
	return (lis_idx);
}

void	ft_push_b(int p_len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	i;
	int	a;
	int	len;

	len = ft_lst_size(*p1) + 1;
	while (len > p_len && *p1)
	{
		a = ft_0_patience(*p1);
		i = ft_lst_size(*p1) - a;
		if (a <= ft_lst_size(*p1) / 2)
			while (a-- > 0)
				ft_swap_rotate("ra", p1, l);
		else
			while (i-- > 0)
				ft_reverse("rra", p1, l);
		ft_push("pb", p2, p1, l);
		p_len++;
	}
}

void	reinsert_b_greedy(t_ps **p1, t_ps **p2, t_action **l)
{
	t_ps	*t;
	int		best_rank;

	best_rank = INT_MAX;
	int best_cost, best_i, i, cost, moves;
	while (*p2)
	{
		t = *p2;
		best_cost = INT_MAX;
		best_i = 0;
		i = 0;
		while (t)
		{
			cost = ft_cost(ft_lst_size(*p1), ft_lst_size(*p2), ft_pos(t->rank,
						*p1), i);
			if (cost < best_cost || (cost == best_cost && t->rank < best_rank))
			{
				best_cost = cost;
				best_rank = t->rank;
				best_i = i;
			}
			t = t->next;
			i++;
		}
		if (best_i <= ft_lst_size(*p2) / 2)
		{
			moves = best_i;
			while (moves-- > 0)
				ft_swap_rotate("rb", p2, l);
		}
		else
		{
			moves = ft_lst_size(*p2) - best_i;
			while (moves-- > 0)
				ft_reverse("rrb", p2, l);
		}
		execute_rotations(p1, p2, ft_pos((*p2)->rank, *p1), 0, ft_lst_size(*p1),
			ft_lst_size(*p2), l);
		ft_push("pa", p1, p2, l);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_2_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:02 by codk              #+#    #+#             */
/*   Updated: 2025/05/05 10:12:46 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		prev[i] = (left > 0 ? pos[left - 1] : -1);
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

void	ft_push_b(int len, int lis_len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	while (i < len - lis_len && *p1)
	{
		pos = ft_get_next_non_lis(*p1);
		if (pos < 0 || pos >= ft_list_size(*p1))
			break ;
		if (pos <= ft_list_size(*p1) / 2)
			while (pos-- > 0)
				ft_swap_rotate("ra", p1, l);
		else
		{
			j = ft_list_size(*p1) - pos;
			while (j-- > 0)
				ft_reverse("rra", p1, l);
		}
		ft_push("pb", p2, p1, l);
		i++;
	}
}

int	ft_get_next_non_lis(t_ps *p)
{
	int	i;

	i = 0;
	while (p)
	{
		if (p->patience == 0)
			return (i);
		p = p->next;
		i++;
	}
	return (-1);
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
			cost = ft_get_cost(ft_list_size(*p1), ft_list_size(*p2), ft_get_target_pos(*p1, t->rank), i);
			if (cost < best_cost || (cost == best_cost && t->rank < best_rank))
			{
				best_cost = cost;
				best_rank = t->rank;
				best_i = i;
			}
			t = t->next;
			i++;
		}
		if (best_i <= ft_list_size(*p2) / 2)
		{
			moves = best_i;
			while (moves-- > 0)
				ft_swap_rotate("rb", p2, l);
		}
		else
		{
			moves = ft_list_size(*p2) - best_i;
			while (moves-- > 0)
				ft_reverse("rrb", p2, l);
		}
		execute_rotations(p1, p2, ft_get_target_pos(*p1, (*p2)->rank), 0,
			ft_list_size(*p1), ft_list_size(*p2), l);
		ft_push("pa", p1, p2, l);
	}
}

int	ft_get_cost(int len_1, int len_2, int pos_a, int pos_b)
{
	int up_up;
	int down_down;
	int up_down;
	int down_up;

	up_up = pos_a > pos_b ? pos_a : pos_b;
	down_down = (len_1 - pos_a) > (len_2 - pos_b) ? (len_1 - pos_a) : (len_2
			- pos_b);
	up_down = pos_a + (len_2 - pos_b);
	down_up = (len_1 - pos_a) + pos_b;

	int cost = up_up;
	if (down_down < cost)
		cost = down_down;
	if (up_down < cost)
		cost = up_down;
	if (down_up < cost)
		cost = down_up;
	return (cost);
}
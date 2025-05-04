/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_2_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:02 by codk              #+#    #+#             */
/*   Updated: 2025/05/05 00:13:48 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	*ft_tab_add_patience(int *tab, int len, int *out_lis_len)
{
	int	i;
	int	j;
	int	k;
	int	*tail;
	int	*pos;
	int	*prev;
	int	lis_end;
	int	*lis_idx;

	i = 0;
	lis_end = 0;
	tail = malloc(sizeof *tail * len);
	pos = malloc(sizeof *pos * len);
	prev = malloc(sizeof *prev * len);
	while (i < len)
	{
		j = 0;
		k = lis_end;
		while (j < k)
		{
			if (tail[(j + k) / 2] < tab[i])
				j = ((j + k) / 2) + 1;
			else
				k = (j + k) / 2;
		}
		tail[j] = tab[i];
		pos[j] = i;
		prev[i] = (j > 0 ? pos[j - 1] : -1);
		if (j + 1 > lis_end)
			lis_end = j + 1;
		i++;
	}
	*out_lis_len = lis_end;
	lis_idx = malloc(sizeof *lis_idx * lis_end);
	k = pos[lis_end - 1];
	i = lis_end - 1;
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
	int	pushed;
	int	to_push;

	pushed = 0;
	to_push = len - lis_len;
	int pos, sz, moves;
	while (pushed < to_push && *p1)
	{
		sz = ft_list_size(*p1);
		pos = ft_get_next_non_lis(*p1);
		if (pos < 0 || pos >= sz)
			break ;
		if (pos <= sz / 2)
		{
			while (pos-- > 0)
				ft_swap_rotate("ra", p1, p2, l);
		}
		else
		{
			moves = sz - pos;
			while (moves-- > 0)
				ft_reverse("rra", p1, p2, l);
		}
		ft_push("pb", p2, p1, l);
		pushed++;
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
	t_ps	*tmp;

	best_rank = INT_MAX;
	int sz_a, sz_b;
	int best_cost, best_i, i, cost, moves, pos_a;
	while (*p2)
	{
		sz_a = ft_list_size(*p1);
		sz_b = ft_list_size(*p2);
		printf(">>> A = ");
		tmp = *p1;
		while (tmp)
		{
			printf("%d ", tmp->rank);
			tmp = tmp->next;
		}
		printf("\n");
		printf(">>> B = ");
		tmp = *p2;
		while (tmp)
		{
			printf("%d ", tmp->rank);
			tmp = tmp->next;
		}
		printf("\n");
		t = *p2;
		best_cost = INT_MAX;
		best_i = 0;
		i = 0;
		while (t)
		{
			pos_a = ft_get_target_pos(*p1, t->rank);
			printf("   target_pos(%2d) = %d\n", t->rank, pos_a);
			cost = ft_get_cost(sz_a, sz_b, pos_a, i);
			printf("  candidat B[%d]=%d → posA=%d, cost=%d\n", i, t->rank,
				pos_a, cost);
			if (cost < best_cost || (cost == best_cost
					&& t->rank < best_rank))
			{
				best_cost = cost;
				best_rank = t->rank;
				best_i = i;
			}
			t = t->next;
			i++;
		}
		if (best_i <= sz_b / 2)
		{
			moves = best_i;
			while (moves-- > 0)
				ft_swap_rotate("rb", p2, p1, l);
		}
		else
		{
			moves = sz_b - best_i;
			while (moves-- > 0)
				ft_reverse("rrb", p2, p1, l);
		}
		sz_a = ft_list_size(*p1);
		sz_b = ft_list_size(*p2);
		pos_a = ft_get_target_pos(*p1, (*p2)->rank);
		execute_rotations(p1, p2, pos_a, 0, sz_a, sz_b, l);
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
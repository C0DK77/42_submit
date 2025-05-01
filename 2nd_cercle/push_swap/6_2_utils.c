/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_2_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:02 by codk              #+#    #+#             */
/*   Updated: 2025/05/01 15:01:21 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	*ft_tab_add_patience(int *tab, int len, int *lis_len)
{
	int	i;
	int	*tail;
	int	*pos;
	int	*prev;
	int	lis_end;
	int	x;
	int	l;
	int	r;
	int	m;
	int	*lis_idx;
	int	k;

	lis_end = 0;
	tail = malloc(sizeof(*tail) * len);
	pos = malloc(sizeof(*pos) * len);
	prev = malloc(sizeof(*prev) * len);
	i = 0;
	while (i < len)
	{
		x = tab[i];
		l = 0;
		r = lis_end;
		while (l < r)
		{
			m = (l + r) / 2;
			if (tail[m] < x)
				l = m + 1;
			else
				r = m;
		}
		tail[l] = x;
		pos[l] = i;
		if (l > 0)
			prev[i] = pos[l - 1];
		else
			prev[i] = -1;
		if (l + 1 > lis_end)
			lis_end = l + 1;
		i++;
	}
	*lis_len = lis_end;
	lis_idx = malloc(sizeof(*lis_idx) * lis_end);
	if (!lis_idx)
	{
		free(tail);
		free(pos);
		free(prev);
		return (NULL);
	}
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

void	ft_push_b(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	i;
	int	pos;
	int	m;

	i = len;
	while (i > 0)
	{
		pos = ft_get_next_non_lis(*p1);
		if (pos >= i)
			break ;
		if (pos <= i / 2)
			while (pos--)
				ft_swap_rotate("ra", 1, p1, p2, l);
		else
		{
			m = i - pos;
			while (m > 0)
			{
				ft_reverse("rra", 1, p1, p2, l);
				m--;
			}
		}
		ft_push("pb", p2, p1, l);
		i--;
	}
}

int	ft_get_next_non_lis(t_ps *p)
{
	int	i;

	i = 0;
	while (i && i->patience)
	{
		p = p->next;
		i++;
	}
	return (i);
}


void	reinsert_b_greedy(t_ps **p1, t_ps **p2, t_action **l)
{
	t_ps *t;
	int best_cost;
	int i;
	int cost;
	int best_i;
	while (*p2)
	{
		t = *p2;
		best_cost = INT_MAX;
		best_i = 0;
		i = 0;
		while (t)
		{
			cost = ft_get_cost(ft_list_size(*p1), ft_list_size(*p2),
					ft_get_target_pos(*p1, t->rank), i);
			if (cost < best_cost)
			{
				best_cost = cost;
				best_i = i;
			}
			t = t->next;
			i++;
		}
		if (best_i <= ft_list_size(*p2) / 2)
			while (best_i-- > 0)
				ft_swap_rotate("rb", 1, p2, p1, l);
		else
		{
			i = ft_list_size(*p2) - best_i;
			while (i > 0)
			{
				ft_reverse("rrb", 1, p2, p1, l);
				i--;
			}
		}
		execute_rotations(p1, p2, ft_get_target_pos(*p1, (*p2)->rank), 1,
			ft_list_size(*p1), ft_list_size(*p2), l);
		ft_push("pa", p1, p2, l);
	}
}
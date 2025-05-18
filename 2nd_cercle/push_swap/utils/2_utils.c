/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:22:02 by codk              #+#    #+#             */
/*   Updated: 2025/05/18 17:59:59 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	*ft_tab_add_patience(int *tab, int len, int *patience_len)
{
	t_patience	patience;
	int			i;
	int			j;
	int			*p;

	patience.nb = malloc(sizeof(*patience.nb) * len);
	patience.i = malloc(sizeof(*patience.i) * len);
	patience.pr_i = malloc(sizeof(*patience.pr_i) * len);
	ft_build_patience(tab, len, patience, patience_len);
	p = malloc(sizeof(*p) * (*patience_len));
	j = patience.i[*patience_len - 1];
	i = *patience_len - 1;
	while (i >= 0)
	{
		p[i] = j;
		j = patience.pr_i[j];
		i--;
	}
	ft_free_multiple(3, patience.nb, patience.i, patience.pr_i);
	return (p);
}

void	ft_build_patience(int *tab, int len, t_patience patience,
		int *patience_len)
{
	int	i;
	int	j;

	i = 0;
	*patience_len = 0;
	while (i < len)
	{
		j = ft_patience_pos(patience.nb, *patience_len, tab[i]);
		patience.nb[j] = tab[i];
		patience.i[j] = i;
		if (j > 0)
			patience.pr_i[i] = patience.i[j - 1];
		else
			patience.pr_i[i] = -1;
		if (j + 1 > *patience_len)
			*patience_len = j + 1;
		i++;
	}
}

int	ft_patience_pos(int *nb, int patience_len, int patience_i)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = patience_len;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (nb[mid] < patience_i)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

void	ft_push_b(int p_len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	i;
	int	a;
	int	len;

	len = ft_lst_size(*p1);
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

int	ft_find_best(t_ps *p1, t_ps *p2, int *best_i)
{
	t_best	best;
	t_ps	*t;
	int		c;
	int		i;

	best.cost = INT_MAX;
	best.rank = INT_MAX;
	best.i = 0;
	t = p2;
	i = 0;
	while (t)
	{
		c = ft_cost(ft_lst_size(p1), ft_lst_size(p2), ft_pos(t->rank, p1), i);
		if (c < best.cost || (c == best.cost && t->rank < best.rank))
		{
			best.cost = c;
			best.rank = t->rank;
			best.i = i;
		}
		t = t->next;
		i++;
	}
	*best_i = best.i;
	return (best.cost);
}

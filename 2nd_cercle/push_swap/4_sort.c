/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/07 16:22:07 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	if (ft_verif_ranking(p1))
		return ;
	if (len == 2)
		ft_swap_rotate("sa", p1, l);
	else if (len <= 3)
		ft_sort_three(p1, l);
	else
		ft_sort_big(len, p1, p2, l);
}

void	ft_sort_three(t_ps **p, t_action **l)
{
	int	a;
	int	b;

	a = ft_rank("min", 0, *p);
	b = ft_rank("max", 0, *p);
	if (ft_rank("", a, *p) == 0)
	{
		ft_swap_rotate("sa", p, l);
		ft_swap_rotate("ra", p, l);
	}
	else if (ft_rank("", b - 1, *p) == 0 && ft_rank("", a, *p) == 1)
		ft_swap_rotate("sa", p, l);
	else if (ft_rank("", a - 1, *p) == 0 && ft_rank("", b, *p) == 1)
		ft_reverse("rra", p, l);
	else if (ft_rank("", b, *p) == 0 && ft_rank("", a, *p) == 1)
		ft_swap_rotate("ra", p, l);
	else if (ft_rank("", b, *p) == 0 && ft_rank("", b - 1, *p) == 1)
	{
		ft_swap_rotate("ra", p, l);
		ft_swap_rotate("sa", p, l);
	}
}

void	ft_sort_big(int len, t_ps **p1, t_ps **p2, t_action **l)
{
	int	*tab;
	int	*lis_i;
	int	lis_l;
	printf("\n\n%i\n\n", len);
	tab = ft_create_tab(*p1, len);
	lis_i = ft_tab_add_patience(tab, len, &lis_l);
	free(tab);
	ft_append_patience(*p1, lis_i, lis_l);
	ft_print(p1, p2, l);
	ft_push_b(lis_l, p1, p2, l);
	ft_print(p1, p2, l);
	reinsert_b_greedy(p1, p2, l);
	ft_print(p1, p2, l);
	final_rotate_a(p1, l);
	free(lis_i);
}

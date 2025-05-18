/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:46:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/16 17:17:37 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_sort(t_ps **p1, t_ps **p2, t_action **l)
{
	int	len;

	len = ft_lst_size(*p1);
	if (ft_verif_ranking(p1))
		return ;
	if (len == 2)
		ft_swap_rotate("sa", p1, l);
	else if (len <= 3)
		ft_sort_three(p1, l);
	else
		ft_sort_big(p1, p2, l);
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

void	ft_sort_big(t_ps **p1, t_ps **p2, t_action **l)
{
	int	*tab;
	int	*patience_i;
	int	patience_len;
	int	best_i;

	tab = ft_create_tab(*p1);
	patience_i = ft_tab_add_patience(tab, ft_lst_size(*p1), &patience_len);
	free(tab);
	ft_append_patience(*p1, patience_i, patience_len);
	ft_push_b(patience_len, p1, p2, l);
	while (*p2)
	{
		ft_find_best(*p1, *p2, &best_i);
		ft_push_a(p1, p2, best_i, l);
		ft_print(p1, p2, l);
	}
	final_rotate_a(p1, l);
	ft_print(p1, p2, l);
	free(patience_i);
}

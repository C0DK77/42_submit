/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_funct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:14 by codk              #+#    #+#             */
/*   Updated: 2025/05/01 14:59:25 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_swap_rotate(char *a, int b, t_ps **p1, t_ps **p2, t_action **l)
{
	t_ps	*n1;
	t_ps	*n2;

	if (!*p1 || !(*p1)->next)
		return ;
	n1 = *p1;
	if (a[0] == 's')
	{
		n2 = n1->next;
		n1->next = n2->next;
		n2->next = n1;
		*p1 = n2;
	}
	else
	{
		n2 = *p1;
		while (n2->next)
			n2 = n2->next;
		*p1 = n1->next;
		n1->next = NULL;
		n2->next = n1;
	}
	ft_append_node_actions(l, a);
	if (b == 0)
		ft_try_reverse(a, 1, p2, p1, l);
}

void	ft_push(char *a, t_ps **p1, t_ps **p2, t_action **l)
{
	t_ps	*n1;

	n1 = *p2;
	*p2 = n1->next;
	n1->next = *p1;
	*p1 = n1;
	ft_append_node_actions(l, a);
}

void	ft_reverse(char *a, int b, t_ps **p1, t_ps **p2, t_action **l)
{
	t_ps	*n1;
	t_ps	*n2;

	n1 = *p1;
	n2 = *p1;
	while (n2->next)
	{
		n1 = n2;
		n2 = n2->next;
	}
	n1->next = NULL;
	n2->next = *p1;
	*p1 = n2;
	ft_append_node_actions(l, a);
	if (b == 0)
		ft_try_reverse(a, b, p2, p1, l);
}

void	ft_try_reverse(char *a, int b, t_ps **p2, t_ps **p1, t_action **l)
{
	int last_rank;

	if (!*p2 || !(*p2)->next)
		return ;

	last_rank = ft_get_position(*p2, "last");

	if (ft_strcmp(a, "sa") == 0 && (*p2)->rank < (*p2)->next->rank)
		ft_swap_rotate("sb", b, p2, p1, l);
	else if (ft_strcmp(a, "sb") == 0 && (*p2)->rank < (*p2)->next->rank)
		ft_swap_rotate("sa", b, p1, p2, l);
	else if (ft_strcmp(a, "ra") == 0 && (*p2)->rank < last_rank)
		ft_swap_rotate("rb", b, p2, p1, l);
	else if (ft_strcmp(a, "rb") == 0 && (*p2)->rank > last_rank)
		ft_swap_rotate("ra", b, p1, p2, l);
	else if (ft_strcmp(a, "rra") == 0 && (*p2)->rank < last_rank)
		ft_swap_rotate("rrb", b, p2, p1, l);
	else if (ft_strcmp(a, "rrb") == 0 && (*p2)->rank < last_rank)
		ft_swap_rotate("rra", b, p1, p2, l);
}
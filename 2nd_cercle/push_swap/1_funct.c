/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_funct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:14 by codk              #+#    #+#             */
/*   Updated: 2025/05/05 00:08:12 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_swap_rotate(char *a, t_ps **p1, t_ps **p2, t_action **l)
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

void	ft_reverse(char *a, t_ps **p1, t_ps **p2, t_action **l)
{
	t_ps *n1;
	t_ps *n2;

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
}
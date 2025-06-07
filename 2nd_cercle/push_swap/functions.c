/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:14 by codk              #+#    #+#             */
/*   Updated: 2025/05/27 16:29:32 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_swap_rotate(char *a, t_ps **p, t_action **l)
{
	t_ps	*n1;
	t_ps	*n2;

	if (!*p || !(*p)->next)
		return ;
	n1 = *p;
	if (a[0] == 's')
	{
		n2 = n1->next;
		n1->next = n2->next;
		n2->next = n1;
		*p = n2;
	}
	else
	{
		n2 = *p;
		while (n2->next)
			n2 = n2->next;
		*p = n1->next;
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

void	ft_reverse(char *a, t_ps **p, t_action **l)
{
	t_ps	*n1;
	t_ps	*n2;

	n1 = *p;
	n2 = *p;
	while (n2->next)
	{
		n1 = n2;
		n2 = n2->next;
	}
	n1->next = NULL;
	n2->next = *p;
	*p = n2;
	ft_append_node_actions(l, a);
}

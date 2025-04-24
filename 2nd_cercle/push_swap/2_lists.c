/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ps_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:24:53 by codk              #+#    #+#             */
/*   Updated: 2025/04/18 22:38:38 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_append_node_piles(t_ps **head, int nb)
{
	t_ps	*n1;
	t_ps	*n2;

	n2 = malloc(sizeof(t_ps));
	if (!n2)
		return ;
	n2->nb = nb;
	n2->next = NULL;
	if (!*head)
		*head = n2;
	else
	{
		n1 = *head;
		while (n1->next)
			n1 = n1->next;
		n1->next = n2;
	}
}

void	ft_append_ranking(t_ps **p)
{
	int		rank;
	t_ps	*n1;
	t_ps	*n2;

	n1 = *p;
	while (n1)
	{
		rank = 1;
		n2 = *p;
		while (n2)
		{
			if (n1->nb > n2->nb)
				rank++;
			n2 = n2->next;
		}
		n1->rank = rank;
		n1 = n1->next;
	}
}

void	ft_append_node_actions(t_action **head, char *action)
{
	t_action *n1;
	t_action *n2;

	n2 = malloc(sizeof(t_action));
	if (!n2)
		return ;
	n2->action = action;
	n2->next = NULL;
	if (!*head)
		*head = n2;
	else
	{
		n1 = *head;
		while (n1->next)
			n1 = n1->next;
		n1->next = n2;
	}
}
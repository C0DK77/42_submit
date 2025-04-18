/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:14 by codk              #+#    #+#             */
/*   Updated: 2025/04/18 20:45:24 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_functions(char *a, t_ps_list **pile, t_ps_list_action **list)
{
	t_ps_list	*node1;
	t_ps_list	*node2;

	if (!pile || !*pile || !(*pile)->next)
		return ;
	node1 = *pile;
	if (a[0] == 's')
	{
		node2 = node1->next;
		node1->next = node2->next;
		node2->next = node1;
		*pile = node2;
	}
	if (a[0] == 'r')
	{
		node2 = *pile;
		while (node2->next)
			node2 = node2->next;
		*pile = node1->next;
		node1->next = NULL;
		node2->next = node1;
	}
	ft_append_node_list(list, a);
}

void	ft_function_revert(char *a, t_ps_list **pile, t_ps_list_action **list)
{
	t_ps_list	*node1;
	t_ps_list	*node2;

	if (!pile || !*pile || !(*pile)->next)
		return ;
	node1 = *pile;
	node2 = *pile;
	while (node2->next)
	{
		node1 = node2;
		node2 = node2->next;
	}
	node1->next = NULL;
	node2->next = *pile;
	*pile = node2;
	ft_append_node_list(list, a);
}

void	ft_function_push(char *a, t_ps_list **pile_1, t_ps_list **pile_2,
		t_ps_list_action **list)
{
	t_ps_list	*node;

	if (!pile_1 || !*pile_1)
		return ;
	node = *pile_1;
	*pile_1 = node->next;
	node->next = *pile_2;
	*pile_2 = node;
	ft_append_node_list(list, a);
}

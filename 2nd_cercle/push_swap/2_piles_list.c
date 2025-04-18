/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_piles_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:24:53 by codk              #+#    #+#             */
/*   Updated: 2025/04/18 20:45:36 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_append_node(t_ps_list **head, int nb)
{
	t_ps_list	*node;
	t_ps_list	*new_node;

	new_node = malloc(sizeof(t_ps_list));
	if (!new_node)
		return ;
	new_node->nb = nb;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
}

void	ft_append_rank(t_ps_list **pile)
{
	int			rank;
	t_ps_list	*node1;
	t_ps_list	*node2;

	node1 = *pile;
	while (node1)
	{
		rank = 1;
		node2 = *pile;
		while (node2)
		{
			if (node1->nb > node2->nb)
				rank++;
			node2 = node2->next;
		}
		node1->rank = rank;
		node1 = node1->next;
	}
}

void	ft_append_node_list(t_ps_list_action **head, char *action)
{
	t_ps_list_action *node;
	t_ps_list_action *new_node;

	new_node = malloc(sizeof(t_ps_list_action));
	if (!new_node)
		return ;
	new_node->action = action;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
}
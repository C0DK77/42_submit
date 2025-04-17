/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_creation_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:24:53 by codk              #+#    #+#             */
/*   Updated: 2025/04/17 18:29:42 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	ft_list_size(t_ps_list **pile)
{
	int	i;

	i = 0;
	while (pile)
	{
		pile = pile->next;
		i++;
	}
	return (i);
}

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

	
	while (node1)
	{
		rank = 1;
		node2 = *pile;
		while (node1)
		{
			if (node1->nb > node2->nb)
				rank++;
			node2 = node2->next;
		}
		node1->rank = rank;
		node1 = node1->next;
	}
}

int	ft_max_rank(t_ps_list **pile)
{
	int	max;

	max = pile->rank;
	while (pile)
	{
		if (pile->rank > max)
			max = pile->rank;
		pile = pile->next;
	}
	return (max);
}

int	ft_get_position(t_ps_list **pile, int target)
{
	int	i;

	i = 0;
	while (pile)
	{
		if (pile->rank == target)
			return (i);
		pile = pile->next;
		i++;
	}
	return (-1);
}

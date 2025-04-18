/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_creation_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:24:53 by codk              #+#    #+#             */
/*   Updated: 2025/04/18 17:59:48 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	ft_list_size(t_ps_list *pile)
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

int	ft_max_min_rank(char a, t_ps_list *pile)
{
	int	max;
	int	min;

	max = pile->rank;
	min = pile->rank;
	while (pile)
	{
		if (pile->rank > max)
			max = pile->rank;
		if (pile->rank < min)
			min = pile->rank;
		pile = pile->next;
	}
	if (a == 'x')
		return (max);
	else
		return (min);
}

int	ft_get_position(t_ps_list *pile, int target)
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

void	ft_append_node_liste(t_ps_list_action **head, char *action)
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
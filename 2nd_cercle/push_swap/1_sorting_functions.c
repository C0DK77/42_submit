/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sorting_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:14 by codk              #+#    #+#             */
/*   Updated: 2025/04/01 15:28:39 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_list_swap(t_ps_list **pile)
{
	t_ps_list	*first_node;
	t_ps_list	*second_node;

	ft_putstr("swap\n");
	if (!pile || !*pile || !(*pile)->next)
		return ;
	first_node = *pile;
	second_node = first_node->next;
	first_node->next = second_node->next;
	second_node->next = first_node;
	*pile = second_node;
}

void	ft_list_push(t_ps_list **pile_1, t_ps_list **pile_2)
{
	t_ps_list	*t1;
	t_ps_list	*first_node_pile_1;

	ft_putstr("PUSH\n");
	t1 = *pile_1;
	first_node_pile_1 = t1->next;
	*pile_1 = first_node_pile_1;
	ft_append_node(&*pile_2, t1->nbr, t1->target_node);
	ft_list_reverse_rotate(&*pile_2);
}

void	ft_list_rotate(t_ps_list **pile)
{
	t_ps_list	*first_node;
	t_ps_list	*last_node;

	ft_putstr("rotate\n");
	if (!pile || !*pile || !(*pile)->next)
		return ;
	first_node = *pile;
	last_node = *pile;
	while (last_node->next)
		last_node = last_node->next;
	*pile = first_node->next;
	first_node->next = NULL;
	last_node->next = first_node;
}

void	ft_list_reverse_rotate(t_ps_list **pile)
{
	t_ps_list *prev_last_node;
	t_ps_list *last_node;

	ft_putstr("reverse\n");
	if (!pile || !*pile || !(*pile)->next)
		return ;
	prev_last_node = *pile;
	last_node = *pile;
	while (last_node->next)
	{
		prev_last_node = last_node;
		last_node = last_node->next;
	}
	prev_last_node->next = NULL;
	last_node->next = *pile;
	*pile = last_node;
}
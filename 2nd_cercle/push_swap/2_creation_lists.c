/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_creation_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:24:53 by codk              #+#    #+#             */
/*   Updated: 2025/03/29 14:44:10 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_append_node(t_ps_list **head, int nbr, int target_node)
{
	t_ps_list	*new_node;
	t_ps_list	*t;

	new_node = malloc(sizeof(t_ps_list));
	if (!new_node)
		return ;
	new_node->nbr = nbr;
	new_node->target_node = target_node;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		t = *head;
		while (t->next)
			t = t->next;
		t->next = new_node;
	}
}

//	FONCTION POUR TROUVER LE CLASSEMENT DES NOMBRES

void	ft_append_target_node(t_ps_list **pile)
{
	t_ps_list *tmp1;
	t_ps_list *tmp2;
	int i;

	tmp1 = *pile;
	while (tmp1)
	{
		i = 1;
		tmp2 = *pile;
		while (tmp2)
		{
			if (tmp1->nbr > tmp2->nbr)
				i++;
			tmp2 = tmp2->next;
		}
		tmp1->target_node = i;
		tmp1 = tmp1->next;
	}
}
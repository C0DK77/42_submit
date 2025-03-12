/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:56 by corentindes       #+#    #+#             */
/*   Updated: 2025/03/12 17:56:55 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//	FONCTION LISTE

void	ft_append_node(t_list **head, int nbr)
{
	t_list	*new_node;
	t_list	*t;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->nbr = nbr;
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

//	FONCTIONS DE TRIE

void	ft_list_swap(t_list **pile)
{
	t_list	*first_node;
	t_list	*second_node;

	printf("swap\n");
	if (!pile || !*pile || !(*pile)->next)
		return ;
	first_node = *pile;
	second_node = first_node->next;
	first_node->next = second_node->next;
	second_node->next = first_node;
	*pile = second_node;
}

void	ft_list_push(t_list **pile_1, t_list **pile_2)
{
	t_list	*t1;
	t_list	*t2;
	t_list	*first_node_pile_1;
	t_list	*first_node_pile_2;

	printf("PUSH\n");
	t1 = *pile_1;
	first_node_pile_1 = t1->next;
	*pile_1 = first_node_pile_1;
	ft_append_node(&*pile_2, t1->nbr);
	ft_list_reverse_rotate(&*pile_2);
}

void	ft_list_rotate(t_list **pile)
{
	t_list	*first_node;
	t_list	*last_node;

	printf("rotate\n");
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

void	ft_list_reverse_rotate(t_list **pile)
{
	t_list	*prev_last_node;
	t_list	*last_node;

	printf("reverse\n");
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

//	FONCTION PRINT PILE

void	ft_print_pile(t_list *pile_a, t_list *pile_b)
{
	int i;

	i = 0;
	printf("PILE_A\n");
	while (pile_a)
	{
		printf("noeud : %i -> entier : %i -> adresse : %p \n", i, pile_a->nbr,
			pile_a);
		pile_a = pile_a->next;
		i++;
	}
	i = 0;
	printf("PILE_B\n");
	while (pile_b)
	{
		printf("noeud : %i -> entier : %i -> adresse : %p \n", i, pile_b->nbr,
			pile_b);
		pile_b = pile_b->next;
		i++;
	}
}
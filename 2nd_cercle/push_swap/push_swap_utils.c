/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:56 by corentindes       #+#    #+#             */
/*   Updated: 2025/03/25 18:46:25 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//	FONCTION LISTE

void	ft_append_node(t_list **head, int nbr, int target_node)
{
	t_list	*new_node;
	t_list	*t;

	new_node = malloc(sizeof(t_list));
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

void	ft_append_target_node(t_list **pile)
{
	t_list	*tmp1;
	t_list	*tmp2;
	int		t_target_node;
	int		i;

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
	ft_append_node(&*pile_2, t1->nbr, t1->target_node);
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

//	FONCTION DE CLASSEMENT ENTRE A ET B

void	ft_split_list_between_a_and_b(t_list **pile_a, t_list **pile_b, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if ((*pile_a)->target_node <= (ac - 1) / 3)
		{
			ft_list_push(pile_a, pile_b);
			ft_list_rotate(pile_b);
		}
		else if ((ac - 1) / 3 < (*pile_a)->target_node
			&& (*pile_a)->target_node <= ((ac - 1) / 3) * 2)
		{
			ft_list_push(pile_a, pile_b);
		}
		else if (((ac - 1) / 3) * 2 < (*pile_a)->target_node)
		{
			ft_list_rotate(pile_a);
		}
		i++;
	}
}

//	FONCTION VERIFICATION NBR

// int	ft_verif_nbr(t_list **pile_a, int ac)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (i < ac)
// 	{
// 		if ((*pile_a)->nbr < (*pile_a)->next->nbr)
// 			j = 1;
// 		i++;
// 	}
// 	return (j);
// }

//	FONCTION VERIFICATION TRIE

int	ft_verif_classement(t_list **pile_a, int ac)
{
	t_list *tmp;

	tmp = *pile_a;
	while (tmp->next)
	{
		if (tmp->nbr > tmp->next->nbr)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

//	FONCTION PRINT PILE

void	ft_print_pile(t_list *pile_a, t_list *pile_b, int ac)
{
	int i;
	int low_value;
	int medium_value;
	int high_value;

	i = 1;
	low_value = (ac - 1) / 3;
	medium_value = (ac - 1) / 3 * 2;
	high_value = ac - 1;
	printf("low value : %i\nmedium value : %i\nhigh value : %i\n\n", low_value,
		medium_value, high_value);
	printf("PILE_A\n\n");
	while (pile_a)
	{
		printf("noeud : %i -> entier : %i -> valeur de trie : %i -> adresse : %p \n\n", i, pile_a->nbr, pile_a->target_node, pile_a);
		pile_a = pile_a->next;
		i++;
	}
	i = 1;
	printf("PILE_B\n\n");
	while (pile_b)
	{
		printf("noeud : %i -> entier : %i -> valeur de trie : %i -> adresse : %p \n\n", i, pile_b->nbr, pile_b->target_node, pile_b);
		pile_b = pile_b->next;
		i++;
	}
}

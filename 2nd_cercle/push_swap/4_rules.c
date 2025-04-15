/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rules.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:56 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/15 16:40:43 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_split_list_between_a_and_b(t_ps_list **pile_a, t_ps_list **pile_b,
		int ac)
{
	int	i;
	int	count_a;
	int	count_b;

	i = 1;
	count_a = ac;
	count_b = 0;
	while (i <= ac)
	{
		if ((*pile_a) && (*pile_a)->next
			&& (*pile_a)->target_node == (int)((*pile_a)->next->target_node)
			+ 1)
			ft_list_swap(pile_a);
		if ((*pile_b) && (*pile_b)->next && (int)((*pile_b)->target_node)
			+ 1 == (int)(*pile_b)->next->target_node)
			ft_list_swap(pile_b);
		if ((*pile_a) && (*pile_a)->target_node <= (ac - 1) / 3)
		{
			ft_list_push(pile_a, pile_b);
			ft_list_rotate(pile_b);
			count_a--;
			count_b++;
		}
		else if ((*pile_a) && (ac - 1) / 3 < (*pile_a)->target_node
			&& (*pile_a)->target_node <= ((ac - 1) / 3) * 2)
		{
			ft_list_push(pile_a, pile_b);
			count_a--;
			count_b++;
		}
		else if ((*pile_a) && ((ac - 1) / 3) * 2 < (*pile_a)->target_node)
			ft_list_rotate(pile_a);
		if (count_b == 2)
			ft_rules_2_elements('b', pile_b);
		if (count_a == 2)
			ft_rules_2_elements('a', pile_a);
		if (count_a == 3)
			ft_rules_3_elements_a(pile_a);
		if ((*pile_b) && (*pile_a)
			&& (*pile_a)->target_node == (int)((*pile_b)->target_node) + 1)
		{
			ft_list_push(pile_a, pile_b);
			count_a--;
			count_b++;
		}
		if ((*pile_a) && (*pile_a)->next
			&& (*pile_a)->target_node == (int)((*pile_a)->next->target_node)
			+ 1)
			ft_list_swap(pile_a);
		if ((*pile_b) && (*pile_b)->next && (int)((*pile_b)->target_node)
			+ 1 == (int)(*pile_b)->next->target_node)
			ft_list_swap(pile_b);
		i++;
	}
}

// PUSH IN A

void	ft_push_in_a(t_ps_list **pile_a, t_ps_list **pile_b)
{
	while (*pile_b)
	{
		if ((*pile_b)->next && (*pile_b)->target_node < (*pile_b)->next->target_node)
			ft_list_swap(pile_b);
		if ((*pile_a)->next && (*pile_a)->target_node > (*pile_a)->next->target_node)
			ft_list_swap(pile_a);
		ft_list_push(pile_b, pile_a);
	}
}

//	FONCTIONS POUR AC EN DESSOUS DE 3

void	ft_rules_2_elements(char a, t_ps_list **pile)
{
	if (a == 'b')
	{
		if (ft_verif_classement_a(pile) == 1)
			return ;
		ft_list_swap(pile);
	}
	else
	{
		if (ft_verif_classement_a(pile) == 0)
			return ;
		ft_list_swap(pile);
	}
}

//	FONCTIONS POUR AC EN DESSOUS DE 4

void	ft_rules_3_elements_a(t_ps_list **pile)
{
	t_ps_list *t;
	int min_value;
	int max_value;

	t = *pile;
	while (t && t->next)
	{
		if (t->target_node < min_value)
			min_value = t->target_node;
		if (t->target_node > max_value)
			max_value = t->target_node;
		t = t->next;
	}
	printf("min : %i, max : %i\n", min_value, max_value);
	while (ft_verif_classement_3_a(pile) == 1)
	{
		if ((*pile)->target_node == max_value || (*pile)->target_node == min_value)
			ft_list_reverse_rotate(pile);
		else
			ft_list_swap(pile);
	}
}

// void	ft_split_list_between_a_and_b(t_ps_list **pile_a, t_ps_list **pile_b,
// 	int ac)
// {
// int	i;
// int	count_a;
// int	count_b;

// i = 1;
// count_a = ac;
// count_b = 0;
// while (i <= ac)
// {
// 	if ((*pile_a) && (*pile_a)->next
// 		&& (*pile_a)->target_node == (int)((*pile_a)->next->target_node)
// 		+ 1)
// 		ft_list_swap(pile_a);
// 	if ((*pile_b) && (*pile_b)->next && (int)((*pile_b)->target_node)
// 		+ 1 == (int)(*pile_b)->next->target_node)
// 		ft_list_swap(pile_b);
// 	if ((*pile_a) && (*pile_a)->target_node <= (ac - 1) / 3)
// 	{
// 		ft_list_push(pile_a, pile_b);
// 		ft_list_rotate(pile_b);
// 		count_a--;
// 		count_b++;
// 	}
// 	else if ((*pile_a) && (ac - 1) / 3 < (*pile_a)->target_node
// 		&& (*pile_a)->target_node <= ((ac - 1) / 3) * 2)
// 	{
// 		ft_list_push(pile_a, pile_b);
// 		count_a--;
// 		count_b++;
// 	}
// 	else if ((*pile_a) && ((ac - 1) / 3) * 2 < (*pile_a)->target_node)
// 		ft_list_rotate(pile_a);
// 	if (count_b == 2)
// 		ft_rules_2_elements('b', pile_b);
// 	if (count_a == 2)
// 		ft_rules_2_elements('a', pile_a);
// 	if (count_a == 3)
// 		ft_rules_3_elements(pile_a);
// 	if ((*pile_b) && (*pile_a)
// 		&& (*pile_a)->target_node == (int)((*pile_b)->target_node) + 1)
// 	{
// 		ft_list_push(pile_a, pile_b);
// 		count_a--;
// 		count_b++;
// 	}
// 	if ((*pile_a) && (*pile_a)->next
// 		&& (*pile_a)->target_node == (int)((*pile_a)->next->target_node)
// 		+ 1)
// 		ft_list_swap(pile_a);
// 	if ((*pile_b) && (*pile_b)->next && (int)((*pile_b)->target_node)
// 		+ 1 == (int)(*pile_b)->next->target_node)
// 		ft_list_swap(pile_b);
// 	i++;
// }
// }*/
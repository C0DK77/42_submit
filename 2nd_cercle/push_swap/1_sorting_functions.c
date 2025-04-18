/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sorting_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:20:14 by codk              #+#    #+#             */
/*   Updated: 2025/04/18 18:40:21 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_functions(char *a, t_ps_list **pile, t_ps_list_action **liste)
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
	ft_append_node_list(&liste, a);
	ft_printf("%s\n", a);
}

void	ft_function_revert(char a, t_ps_list **pile, t_ps_list_action **liste)
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
	ft_append_node_list(&liste, ft_strjoin("rr", &a));
	ft_printf("rr%c\n", b);
}

void	ft_function_push(char a, t_ps_list **pile_1, t_ps_list **pile_2, t_ps_list_action **liste)
{
	t_ps_list	*node;

	if (!pile_1 || !*pile_1)
		return ;
	node = *pile_1;
	*pile_1 = node->next;
	node->next = *pile_2;
	*pile_2 = node;
	ft_append_node_list(&liste, ft_strjoin("p", &a));
	ft_printf("p%c\n", a);
}

void	ft_sort(int size, t_ps_list **pile_a, t_ps_list **pile_b, t_ps_list_action **liste)
{
	if (size == 2)
		ft_functions("sa", pile_a, liste);
	else if (size == 3)
		ft_sort_three(pile_a, liste);
	else if (size <= 5)
		ft_sort_five(size, pile_a, pile_b, liste);
}

void	ft_sortin_a(int size, t_ps_list **pile_a, t_ps_list **pile_b, t_ps_list_action **liste)
{
	int	group;

	group = 1;
	while (*pile_a)
	{
		if ((*pile_a)->rank < (size / 5) * group)
		{
			ft_function_push('b', pile_a, pile_b, liste);
			if ((*pile_b)->rank < ((size / 5) * group) - ((size / 5) / 2))
				ft_functions("rb", pile_b, liste);
		}
		else
			ft_functions("ra", pile_a, liste);
		if (!ft_ispartofgroup(pile_a, size / 5 * group))
			group++;
	}
}

void	ft_sortin_b(int size, t_ps_list **pile_a, t_ps_list **pile_b, t_ps_list_action **liste)
{
	while (*pile_b)
	{
		if (ft_get_position(*pile_b, ft_max_min_rank("max", *pile_b)) <= size / 2)
		{
			while ((*pile_b)->rank != ft_max_min_rank("max", *pile_b))
				ft_functions("rb", pile_b, liste);
		}
		else
		{
			while ((*pile_b)->rank != ft_max_min_rank("max", *pile_b))
				ft_function_revert('b', pile_b, liste);
		}
		ft_function_push('a', pile_b, pile_a, liste);
	}
}
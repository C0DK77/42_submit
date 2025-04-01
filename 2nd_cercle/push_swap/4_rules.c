/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rules.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:56 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/01 15:27:55 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_split_list_between_a_and_b(t_ps_list **pile_a, t_ps_list **pile_b, int ac)
{
	int	i;
	int count_b;

	i = 1;
	count_b = 0;
	while (i < ac)
	{
		// if ((*pile_a)->target_node == (*pile_a)->next->target_node + 1)
		// {
		// 	ft_list_swap(pile_a);
		// }
		// if ((*pile_b)->target_node == (*pile_b)->next->target_node + 1
			// && pile_b && *pile_b && (*pile_b)->next)
		// {
		// 	ft_list_swap(pile_b);
		// }
		if ((*pile_a)->target_node <= (ac - 1) / 3)
		{
			ft_list_push(pile_a, pile_b);
			ft_list_rotate(pile_b);
			count_b++;
		}
		else if ((ac - 1) / 3 < (*pile_a)->target_node
			&& (*pile_a)->target_node <= ((ac - 1) / 3) * 2)
		{
			ft_list_push(pile_a, pile_b);
			count_b++;
		}
		else if (((ac - 1) / 3) * 2 < (*pile_a)->target_node)
			ft_list_rotate(pile_a);
		if (count_b == 2)
			ft_rules_2_elements(pile_b);
		if (ac - i == 2)
			ft_rules_2_elements(pile_a);
		i++;
	}
}

void	ft_push_in_a (t_ps_list **pile_a, t_ps_list **pile_b)
{
	int	i;
	int count_b;

	i = 1;
	count_b = 0;
	while (*pile_a)
	{
		ft_list_push(pile_b, pile_a);
		(*pile_b) = (*pile_b)->next;
	}
}

//	FONCTIONS POUR AC EN DESSOUS DE 4

void ft_rules_2_elements (t_ps_list **pile)
{
	if (ft_verif_classement(pile)==0)
		return;
	else
		ft_list_swap(pile);
}

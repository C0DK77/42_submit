/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_rules.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:56 by corentindes       #+#    #+#             */
/*   Updated: 2025/03/28 15:32:30 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ft_split_list_between_a_and_b(t_ps_list **pile_a, t_ps_list **pile_b, int ac)
{
	int	i;

	i = 1;
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
		}
		else if ((ac - 1) / 3 < (*pile_a)->target_node
			&& (*pile_a)->target_node <= ((ac - 1) / 3) * 2)
			ft_list_push(pile_a, pile_b);
		else if (((ac - 1) / 3) * 2 < (*pile_a)->target_node)
			ft_list_rotate(pile_a);
		i++;
	}
}

//	FONCTIONS POUR AC EN DESSOUS DE 4

// void ft_rules_3_elements (t_ps_list **pile_a, t_ps_list **pile_b, int ac, int i)
// {
// 	if (ac < 4)
// 	{

// 	}
// }

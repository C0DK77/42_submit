/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:04 by cdesjars          #+#    #+#             */
/*   Updated: 2025/03/19 19:59:44 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(int ac, char **av)
{
	int		i;
	t_list	*pile_a;
	t_list	*pile_b;

	pile_a = NULL;
	pile_b = NULL;
	// error if no args
	if (ac == 1)
		printf(" Error\n");
	// error if not int
	i = 1;
	// APPENDS NODES FOR EACH VALUE
	while (i < ac)
	{
		ft_append_node(&pile_a, atoi(av[i]), i);
		i++;
	}
	ft_print_pile(pile_a, pile_b, ac);
	ft_append_target_node(&pile_a);
	ft_split_list_between_a_and_b(&pile_a, &pile_b, ac);
	ft_print_pile(pile_a, pile_b, ac);
	// ft_list_swap(&pile_a);
	// ft_print_pile(pile_a, pile_b);
	// ft_list_rotate(&pile_a);
	// ft_print_pile(pile_a, pile_b);
	// ft_list_reverse_rotate(&pile_a);
	// ft_print_pile(pile_a, pile_b);
	// ft_list_push(&pile_a, &pile_b);
	// ft_print_pile(pile_a, pile_b);
}

int	main(int ac, char **av)
{
	push_swap(ac, av);
	return (0);
}
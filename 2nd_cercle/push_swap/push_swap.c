/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:04 by cdesjars          #+#    #+#             */
/*   Updated: 2025/03/15 14:54:06 by corentindes      ###   ########.fr       */
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
	i = 1;
	// APPENDS NODES FOR EACH VALUE
	while (i < ac)
	{
		ft_append_node(&pile_b, atoi(av[i]), i);
		i++;
	}
	ft_print_pile(pile_a, pile_b);
	printf("GGGGGGGGGG\n");
	t_list *tmp;
	int t_target_node;
	tmp = pile_a;
	while (tmp->next)
	{
		if(tmp->nbr > tmp->next->nbr)
		{
			t_target_node = tmp->target_node;
			tmp->target_node = tmp->next->target_node;
			tmp->next->target_node = t_target_node;
			printf("%i -> %i\n", tmp->target_node, tmp->nbr);
		}
		tmp = tmp->next;
	}
	ft_print_pile(pile_a, pile_b);
	ft_list_swap(&pile_a);
	ft_print_pile(pile_a, pile_b);
	ft_list_rotate(&pile_a);
	ft_print_pile(pile_a, pile_b);
	ft_list_reverse_rotate(&pile_a);
	ft_print_pile(pile_a, pile_b);
	ft_list_push(&pile_a, &pile_b);
	ft_print_pile(pile_a, pile_b);
}

int	main(int ac, char **av)
{
	push_swap(ac, av);
	return (0);
}
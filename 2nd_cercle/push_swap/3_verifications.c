/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_verifications.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:04 by codk              #+#    #+#             */
/*   Updated: 2025/03/29 15:44:41 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	ft_verification_args(int ac)
{
	if (ac < 2)
		return (0);
	return (1);
}

int	ft_verif_int(int ac, char **av)
{
	int	i;
	int j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if ((av[i][0] == '-' || av[i][0] == '+') && av[i][1])
			j++;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_verif_classement(t_ps_list **pile_a)
{
	t_ps_list	*tmp;

	tmp = *pile_a;
	while (tmp->next)
	{
		if (tmp->nbr > tmp->next->nbr)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_print_pile(t_ps_list *pile_a, t_ps_list *pile_b, int ac)
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
		printf("noeud : %i -> entier : %i ", i, pile_a->nbr);
		printf("-> valeur de trie : %i", pile_a->target_node);
		printf("-> adresse : %p \n\n", pile_a);
		pile_a = pile_a->next;
		i++;
	}
	i = 1;
	printf("PILE_B\n\n");
	while (pile_b)
	{
		printf("noeud : %i -> entier : %i ", i, pile_b->nbr);
		printf("-> valeur de trie : %i", pile_b->target_node);
		printf("-> adresse : %p \n\n", pile_b);
		pile_b = pile_b->next;
		i++;
	}
}
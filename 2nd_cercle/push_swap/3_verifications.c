/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_verifications.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:04 by codk              #+#    #+#             */
/*   Updated: 2025/04/15 16:57:01 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	ft_verif_args_int(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 2)
		return (0);
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
int	ft_verif_doublons(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 1;
		while (i + j < ac)
		{
			if (av[i] == av[i + j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_verif_classement(char a, t_ps_list **pile)
{
	t_ps_list	*tmp;

	tmp = *pile;
	while (tmp->next)
	{
		if ((tmp->nbr > tmp->next->nbr && a == 'a') || (tmp->nbr < tmp->next->nbr && a == 'b'))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_verif_classement_3_a(t_ps_list **pile)
{
	int			i;
	t_ps_list	*tmp;

	i = 1;
	tmp = *pile;
	while (i < 3)
	{
		if (tmp->nbr > tmp->next->nbr)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	ft_print_pile(t_ps_list **pile_a, t_ps_list **pile_b, int ac)
{
	int i;
	int low_value;
	int medium_value;
	int high_value;
	t_ps_list *t1;
	t_ps_list *t2;

	i = 1;
	t1 = *pile_a;
	t2 = *pile_b;
	low_value = (ac - 1) / 3;
	medium_value = (ac - 1) / 3 * 2;
	high_value = ac - 1;
	printf("low value : %i\nmedium value : %i\nhigh value : %i\n\n", low_value,
		medium_value, high_value);
	printf("PILE_A\n\n");
	while (t1)
	{
		printf("noeud : %i -> entier : %i ", i, t1->nbr);
		printf("-> valeur de trie : %i", t1->target_node);
		printf("-> adresse : %p \n\n", t1);
		t1 = t1->next;
		i++;
	}
	i = 1;
	printf("PILE_B\n\n");
	while (t2)
	{
		printf("noeud : %i -> entier : %i ", i, t2->nbr);
		printf("-> valeur de trie : %i", t2->target_node);
		printf("-> adresse : %p \n\n", t2);
		t2 = t2->next;
		i++;
	}
}
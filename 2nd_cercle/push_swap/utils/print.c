/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:40:19 by codk              #+#    #+#             */
/*   Updated: 2025/05/18 18:48:08 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_print_piles(t_ps **p1, t_ps **p2)
{
	t_ps	*t1;
	t_ps	*t2;

	t1 = *p1;
	t2 = *p2;
	ft_printf("PILE A\n\n");
	while (t1)
	{
		printf("-> entier : %i -> valeur de trie : %i ", t1->nb, t1->rank);
		printf("-> adresse : %p -> patience : %i \n\n", t1, t1->patience);
		t1 = t1->next;
	}
	ft_printf("PILE B\n\n");
	while (t2)
	{
		printf("-> entier : %i -> valeur de trie : %i ", t2->nb, t2->rank);
		printf("-> adresse : %p -> patience : %i \n\n", t2, t2->patience);
		t2 = t2->next;
	}
}

void	ft_print_commandes(t_action **l)
{
	int			i;
	t_action	*t;

	i = 0;
	t = *l;
	ft_printf("COMMANDES\n\n");
	while (t)
	{
		printf("-> commande : %s -> adresse : %p \n\n", t->action, t);
		t = t->next;
		i++;
	}
	ft_printf("\nTOTAL ACTIONS -> %i\n\n", i);
}

void	ft_print_tab(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
}

void	ft_checker(t_ps **p1)
{
	if (ft_verif_ranking(p1))
		ft_printf("\nLE CLASSEMENT EST OK\n");
	else
		ft_printf("\nPROBLEME\n");
}
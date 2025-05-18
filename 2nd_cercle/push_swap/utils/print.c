/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:40:19 by codk              #+#    #+#             */
/*   Updated: 2025/05/16 15:10:47 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_print(t_ps **p1, t_ps **pb, t_action **l)
{
	(void)l;
	t_ps		*t1;
	t_ps		*t2;
	//t_action	*t3;
	//int			i;

	t1 = *p1;
	t2 = *pb;
	//t3 = *l;
	//i = 0;
	ft_printf("PILE 1\n\n");
	while (t1)
	{
		printf("-> entier : %i -> valeur de trie : %i ", t1->nb, t1->rank);
		printf("-> adresse : %p -> patience : %i \n\n", t1, t1->patience);
		t1 = t1->next;
	}
	printf("PILE 2\n\n");
	while (t2)
	{
		printf("-> entier : %i -> valeur de trie : %i ", t2->nb, t2->rank);
		printf("-> adresse : %p -> patience : %i \n\n", t2, t2->patience);
		t2 = t2->next;
	}
	// while (t3)
	// {
	// 	printf("-> index : %i -> commande : %s -> adresse : %p \n\n", i,
	// 		t3->action, t3);
	// 	t3 = t3->next;
	// 	i++;
	// }
}

void	ft_print_tab(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
}

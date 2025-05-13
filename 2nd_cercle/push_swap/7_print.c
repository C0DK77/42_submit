/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:40:19 by codk              #+#    #+#             */
/*   Updated: 2025/05/07 15:47:01 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_print(t_ps **p1, t_ps **pb, t_action **l)
{
	t_ps		*t1;
	t_ps		*t2;
	t_action	*t3;

	t1 = *p1;
	t2 = *pb;
	t3 = *l;
	ft_printf("PILE 1\n\n");
	while (t1)
	{
		printf("-> entier : %i ", t1->nb);
		printf("-> valeur de trie : %i ", t1->rank);
		printf("-> adresse : %p ", t1);
		printf("-> patience : %i \n\n", t1->patience);
		t1 = t1->next;
	}
	printf("PILE 2\n\n");
	while (t2)
	{
		printf("-> entier : %i ", t2->nb);
		printf("-> valeur de trie : %i ", t2->rank);
		printf("-> adresse : %p ", t2);
		printf("-> patience : %i \n\n", t2->patience);
		t2 = t2->next;
	}
	printf("ACTIONS\n\n");
	while (t3)
	{
		printf("-> commande : %s ", t3->action);
		printf("-> adresse : %p \n\n", t3);
		t3 = t3->next;
	}
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

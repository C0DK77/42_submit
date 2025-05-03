/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_verif.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:04 by codk              #+#    #+#             */
/*   Updated: 2025/05/02 14:35:47 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

int	ft_isint(int ac, char **av)
{
	int	i;
	int	j;

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
		if (ft_atoi_long(av[i]) < -2147483648
			|| ft_atoi_long(av[i]) > 2147483647)
			return (0);
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
		j = i + 1;
		while (j < ac)
		{
			if (ft_atoi(av[i]) == ft_atoi(av[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_verif_ranking(t_ps **p)
{
	t_ps	*t;

	t = *p;
	while (t && t->next)
	{
		if (t->nb > t->next->nb)
			return (0);
		t = t->next;
	}
	return (1);
}

void	ft_free(void **list)
{
	void	*t;

	while (*list)
	{
		t = *list;
		*list = *(void **)(*list);
		free(t);
	}
}

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

void ft_print_tab(int *tab, int len)
{
    int i = 0;
    while (i < len)
    {
        printf("%d ", tab[i]);
        i++;
    }
    printf("\n");
}

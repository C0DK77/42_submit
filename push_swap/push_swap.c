/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:04 by cdesjars          #+#    #+#             */
/*   Updated: 2025/02/10 18:23:33 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void init(dblist *l)
{
	l->first = NULL;
	l->last = NULL;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putlst(char *lst)
{
	int	i;

	i = 0;
	while (lst[i++])
		ft_putchar(lst[i]);
}

int	ft_isnbr(int i)
{
	if (-2147483648 <= i && i <= 2147483647)
		return (1);
	return (0);
}

// DONE

void	ft_append_node(t_list **head, int nbr)
{
	t_list	*new_node;
	t_list	*t;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->nbr = nbr;
	new_node->next = NULL;
	printf("%i ->", new_node->nbr);
	if (!*head)
		*head = new_node;
	else
	{
		t = *head;
		while (t->next)
		{
			t = t->next;
			printf(" %p ", new_node->next);
		}
		t->next = new_node;
	}
}

// DONE

void	ft_lst_swap(t_list **pile)
{
	t_list	*t_node_1;
	t_list	*t_node_2;

	t_node_1 = *pile;
	t_node_2 = t_node_1->next;
	printf("%p", t_node_1->next);

	t_node_1->next = t_node_2->next;
	t_node_2->next = t_node_1;
	
	*pile = t_node_2;
}

// TBF

void	ft_lst_rotate(t_list **pile)
{
	t_list	*t_node_1;
	t_list	*t_node_2;

	t_node_1 = *pile;
	t_node_2 = t_node_1->next;
	t_node_1->next = t_node_2->next;
	t_node_2->next = t_node_1;
	*pile = t_node_2;
}

// TBF

void	ft_lst_push(t_list **pile_1, t_list **pile_2)
{
	t_list	*t1;
	t_list	*t2;
	t_list	*t_node_p1;
	t_list	*t_node_p2;

	t1 = *pile_1;
	t_node_p1 = t1->next;
	t2 = *pile_2;
	t_node_p2 = t2->next;
	t1->next = t_node_p2;
	t2->next = t_node_p1;
	*pile_1 = t2;
	*pile_2 = t1;
}

// TBF

void	push_swap(int ac, char **av)
{
	int		i;
	t_list	*pile_a;
	t_list	*pile_b;

	pile_a = NULL;
	// error if no args
	if (ac == 1)
		ft_putlst(" Error\n");
	// error if not int
	i = 1;
	while (i < ac)
	{
		printf("%s\n", av[i]);
		// printf("%i\n", i);
		// printf("%i\n", atoi(av[i]));
		// if (ft_isnbr(atoi(av[i])) == 0)
		//    ft_putlst(" Error\n");
		i++;
	}
	i = 1;
	// APPENDS NODES FOR EACH VALUE
	while (i < ac)
	{
		ft_append_node(&pile_a, atoi(av[i]));
		printf(" %p ", pile_a);
		i++;
	}
	ft_lst_swap(&pile_a);
	i = 1;
	while (i < ac)
	{
		ft_append_node(&pile_a, atoi(av[i]));
		printf(" %p ", pile_a);
		i++;
	}
}

int	main(int ac, char **av)
{
	push_swap(ac, av);
	return (0);
}
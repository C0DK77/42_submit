/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:04 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/27 15:16:44 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	push_swap(int ac, char **av)
{
	int			i;
	t_ps		*p1;
	t_ps		*p2;
	t_action	*l;

	i = 0;
	p1 = NULL;
	p2 = NULL;
	l = NULL;
	if (ft_isint(ac, av) == 0 || ft_verif_doublons(ac, av) == 0)
		return (ft_putstr_fd("Error\n", 2));
	while (i < ac - 1)
	{
		ft_append_node_piles(&p1, ft_atoi(av[i + 1]));
		i++;
	}
	ft_append_ranking(&p1);
	if (ft_verif_ranking(&p1))
		return ;
	ft_sort(i, &p1, &p2, &l);
	ft_action_opti(&l);
	ft_print(&p1, &p2, &l);
	// ft_free((void **)&p1);
	
	// ft_free((void **)&p2);
	// ft_free((void **)&l);
	return ;
}

int	main(int ac, char **av)
{
	push_swap(ac, av);
	return (0);
}
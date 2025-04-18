/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:04 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/18 20:47:40 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	push_swap(int ac, char **av)
{
	int					size;
	t_ps_list			*pile_a;
	t_ps_list			*pile_b;
	t_ps_list_action	*list;

	size = 0;
	pile_a = NULL;
	pile_b = NULL;
	list = NULL;
	if (ft_isint(ac, av) == 0 || ft_verif_doublons(ac, av) == 0)
		return (ft_putstr_fd("Error\n", 2));
	while (size < ac - 1)
	{
		ft_append_node(&pile_a, ft_atoi(av[size + 1]));
		size++;
	}
	ft_append_rank(&pile_a);
	if (ft_verif_ranking('a', &pile_a))
		return ;
	if (size <= 5)
		ft_sort(size, &pile_a, &pile_b, &list);
	else
	{
		ft_sortin_a(size, &pile_a, &pile_b, &list);
		ft_sortin_b(size, &pile_a, &pile_b, &list);
	}
	ft_print_pile(&pile_a, &pile_b, &list);
	ft_free_pile(&pile_a, &pile_b, &list);
	return ;
}

int	main(int ac, char **av)
{
	push_swap(ac, av);
	return (0);
}
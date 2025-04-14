/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:49:04 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/14 17:35:47 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	push_swap(int ac, char **av)
{
	int			i;
	t_ps_list	*pile_a;
	t_ps_list	*pile_b;

	i = 1;
	pile_a = NULL;
	pile_b = NULL;
	if (ft_verification_args(ac) == 0)
		return ;
	if (ft_verif_int(ac, av) == 0)
		return (ft_putstr("Error\n"));
	while (i < ac)
	{
		ft_append_node(&pile_a, ft_atoi(av[i]), i);
		i++;
	}
	ft_append_target_node(&pile_a);
	if (ft_verif_classement(&pile_a) == 0)
		return (ft_putstr("La liste est classee !\n"));
	if (ft_verif_doublons(&pile_a) == 1)
		return (ft_putstr("Doublons\n"));
	ft_print_pile(&pile_a, &pile_b, ac);
	ft_split_list_between_a_and_b(&pile_a, &pile_b, ac);
	ft_print_pile(&pile_a, &pile_b, ac);
	ft_push_in_a(&pile_a, &pile_b);
	ft_print_pile(&pile_a, &pile_b, ac);
}

int	main(int ac, char **av)
{
	push_swap(ac, av);
	return (0);
}
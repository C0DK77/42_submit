/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_verifications.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:04 by codk              #+#    #+#             */
/*   Updated: 2025/04/18 10:27:53 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

long	ft_atoi_long(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

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

int	ft_verif_ranking(char a, t_ps_list **pile)
{
	t_ps_list	*tp;

	tp = *pile;
	while (tp && tp->next)
	{
		if ((a == 'a' && tp->nb > tp->next->nb) || (a == 'b' && tp->nb < tp->next->nb))
			return (0);
		tp = tp->next;
	}
	return (1);
}

int	ft_ispartofgroup(t_ps_list **pile, int target)
{
	t_ps_list	*tp;

	tp = *pile;
	while (tp)
	{
		if (tp->rank < target)
			return (1);
		tp = tp->next;
	}
	return (0);
}

void	ft_print_pile(t_ps_list **pile_a, t_ps_list **pile_b)
{
	t_ps_list	*tp1;
	t_ps_list	*tp2;

	tp1 = *pile_a;
	tp2 = *pile_b;
	ft_printf("PILE_A\n\n");
	while (tp1)
	{
		printf("-> entier : %i ", tp1->nb);
		printf("-> valeur de trie : %i", tp1->rank);
		printf("-> adresse : %p \n\n", tp1);
		tp1 = tp1->next;
	}
	printf("PILE_B\n\n");
	while (tp2)
	{
		printf("-> entier : %i ", tp2->nb);
		printf("-> valeur de trie : %i", tp2->rank);
		printf("-> adresse : %p \n\n", tp2);
		tp2 = tp2->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:23:04 by codk              #+#    #+#             */
/*   Updated: 2025/05/16 15:40:52 by corentindes      ###   ########.fr       */
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

void	ft_free_multiple(int ac, ...)
{
	int		i;
	va_list	av;
	void	*p;

	va_start(av, ac);
	i = 0;
	while (i < ac)
	{
		p = va_arg(av, void *);
		free(p);
		i++;
	}
	va_end(av);
}

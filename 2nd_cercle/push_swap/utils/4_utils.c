/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:58:13 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/18 18:40:34 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	final_rotate_a(t_ps **p, t_action **l)
{
	int	i;

	i = ft_rank("", ft_rank("min", 0, *p), *p);
	if (i <= ft_lst_size(*p) / 2)
	{
		while (i > 0)
		{
			ft_swap_rotate("ra", p, l);
			i--;
		}
	}
	else
	{
		i = ft_lst_size(*p) - i;
		while (i > 0)
		{
			ft_reverse("rra", p, l);
			i--;
		}
	}
}

void	ft_action_opti(t_action **l)
{
	t_action	*t;

	t = *l;
	while (t)
	{
		if (t->next && t->next->next && ft_action_dif(t->action,
				t->next->action))
			t = t->next->next;
		if (t->next && !(t->next->next) && ft_action_dif(t->action,
				t->next->action))
			t = t->next;
		else
		{
			ft_printf("%s\n", t->action);
			t = t->next;
		}
	}
}

int	ft_action_dif(char *a1, char *a2)
{
	if (ft_strcmp(a1, "ra") == 0 && ft_strcmp(a2, "rb") == 0)
		ft_printf("rr\n");
	else if (ft_strcmp(a1, "rb") == 0 && ft_strcmp(a2, "ra") == 0)
		ft_printf("rr\n");
	else if (ft_strcmp(a1, "rra") == 0 && ft_strcmp(a2, "rrb") == 0)
		ft_printf("rrr\n");
	else if (ft_strcmp(a1, "rrb") == 0 && ft_strcmp(a2, "rra") == 0)
		ft_printf("rrr\n");
	else if (ft_strcmp(a1, "sa") == 0 && ft_strcmp(a2, "sb") == 0)
		ft_printf("ss\n");
	else if (ft_strcmp(a1, "sb") == 0 && ft_strcmp(a2, "sa") == 0)
		ft_printf("ss\n");
	else
		return (0);
	return (1);
}

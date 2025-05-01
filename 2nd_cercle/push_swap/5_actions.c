/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:58:13 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/01 13:20:27 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_action_opti(t_action **l)
{
	int i;
	t_action	*t;
	i = 0;
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
		i++;
	}
	printf("\nTOTAL ACTIONS -> %i\n\n", i);
}

int	ft_action_dif(char *action, char *next_action)
{
	if ((strcmp(action, "ra") == 0 && strcmp(next_action, "rb") == 0)
		|| (strcmp(action, "rb") == 0 && strcmp(next_action, "ra") == 0))
		ft_printf("rr\n");
	else if ((strcmp(action, "rra") == 0 && strcmp(next_action, "rrb") == 0)
		|| (strcmp(action, "rrb") == 0 && strcmp(next_action, "rra") == 0))
		ft_printf("rrr\n");
	else if ((strcmp(action, "sa") == 0 && strcmp(next_action, "sb") == 0)
		|| (strcmp(action, "sb") == 0 && strcmp(next_action, "sa") == 0))
		ft_printf("ss\n");
	else
		return (0);
	return (1);
}
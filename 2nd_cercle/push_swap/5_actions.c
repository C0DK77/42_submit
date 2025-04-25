/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:58:13 by corentindes       #+#    #+#             */
/*   Updated: 2025/04/25 11:45:23 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"

void	ft_action_opti(t_action **l)
{
	t_action	*t;
	t_action	*tp;
	char		*new_action;

	t = *l;
	while (t && t->next)
	{
		if (ft_rules_opti(t->action, t->next->action, &new_action) == 0)
		{
			free(t->action);
			t->action = new_action;
			tp = t->next;
			t->next = t->next->next;
			free(tp->action);
			free(tp);
		}
		else
			t = t->next;
	}
}

int	ft_rules_opti(char *action, char *next_action, char **res)
{
	if ((strcmp(action, "ra") == 0 && strcmp(next_action, "rb") == 0)
		|| (strcmp(action, "rb") == 0 && strcmp(next_action, "ra") == 0))
		*res = strdup("rr");
	else if ((strcmp(action, "rra") == 0 && strcmp(next_action, "rrb") == 0)
		|| (strcmp(action, "rrb") == 0 && strcmp(next_action, "rra") == 0))
		*res = strdup("rrr");
	else if ((strcmp(action, "sa") == 0 && strcmp(next_action, "sb") == 0)
		|| (strcmp(action, "sb") == 0 && strcmp(next_action, "sa") == 0))
		*res = strdup("ss");
	else
		return (1);
	return (0);
}
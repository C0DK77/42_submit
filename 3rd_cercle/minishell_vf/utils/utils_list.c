/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:10 by codk              #+#    #+#             */
/*   Updated: 2025/10/23 09:17:43 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_all	*ft_init_all(int i)
{
	static t_all	a;

	if (i)
	{
		a.ch = NULL;
		a.tk = NULL;
		a.cmd = NULL;
	}
	return (&a);
}

size_t	ft_count_arg(t_element *e)
{
	size_t i;

	i = 0;
	while (e)
	{
		if (e->kind == ARG)
			i++;
		e = e->next;
	}
	return (i);
}

void	ft_fill_argv(t_element *e, char **argv)
{
	size_t	i;

	i = 0;
	while (e)
	{
		if (e->kind == ARG)
		{
			if (e->u_.arg)
				argv[i] = e->u_.arg->str;
			else
				argv[i] = NULL;
			i++;
		}
		e = e->next;
	}
	argv[i] = NULL;
}
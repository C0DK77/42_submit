/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:18:50 by cdesjars          #+#    #+#             */
/*   Updated: 2025/08/23 09:46:34 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **l, void (*del)(void *))
{
	t_list	*t;

	if (!l || !del)
		return ;
	while (*l)
	{
		t = (*l)->next;
		del((*l)->content);
		free(*l);
		*l = t;
	}
	*l = NULL;
}

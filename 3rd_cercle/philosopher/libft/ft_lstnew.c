/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:54:16 by cdesjars          #+#    #+#             */
/*   Updated: 2024/12/17 15:56:00 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*strnew;

	strnew = (t_list *)malloc(sizeof(t_list));
	if (!strnew)
		return (NULL);
	strnew->content = content;
	strnew->next = NULL;
	return (strnew);
}

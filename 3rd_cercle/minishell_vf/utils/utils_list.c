/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:10 by codk              #+#    #+#             */
/*   Updated: 2025/10/16 19:13:17 by corentindes      ###   ########.fr       */
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

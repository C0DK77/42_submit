/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:11:56 by corentindes       #+#    #+#             */
/*   Updated: 2024/11/20 16:29:09 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b1, int c, size_t len)
{
	size_t			i;
	unsigned char	*b2;

	i = 0;
	b2 = (unsigned char *)b1;
	while (i < len)
	{
		b2[i] = (unsigned char)c;
		i++;
	}
	return (b1);
}

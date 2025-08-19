/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:11:40 by corentindes       #+#    #+#             */
/*   Updated: 2024/11/20 16:28:45 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*j;
	const unsigned char	*k;

	i = 0;
	j = (const unsigned char *)s1;
	k = (const unsigned char *)s2;
	while (i < n)
	{
		if (j[i] != k[i])
			return (j[i] - k[i]);
		i++;
	}
	return (0);
}

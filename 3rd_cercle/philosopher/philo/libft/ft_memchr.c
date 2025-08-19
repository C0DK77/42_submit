/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:11:36 by corentindes       #+#    #+#             */
/*   Updated: 2024/11/20 16:28:43 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*string;
	unsigned char		value;

	i = 0;
	string = (const unsigned char *)s;
	value = (unsigned char)c;
	while (i < n)
	{
		if (string[i] == value)
			return ((void *)(string + i));
		i++;
	}
	return (NULL);
}

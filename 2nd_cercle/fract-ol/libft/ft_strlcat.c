/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:55:59 by corentindes       #+#    #+#             */
/*   Updated: 2024/11/20 16:54:22 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = i;
	k = 0;
	if (dstsize > 0 && j < dstsize - 1)
	{
		while (src[k] && j + k < dstsize - 1)
		{
			dst[j + k] = src[k];
			k++;
		}
		dst[j + k] = '\0';
	}
	while (src[k])
		k++;
	return (i + k);
}

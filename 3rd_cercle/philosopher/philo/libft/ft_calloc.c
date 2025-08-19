/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:51:37 by corentindes       #+#    #+#             */
/*   Updated: 2024/11/20 18:15:03 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	void			*memory;
	unsigned char	*ptr;

	i = 0;
	memory = malloc(count * size);
	if (!memory)
		return (NULL);
	ptr = (unsigned char *)memory;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_char_to_bit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:51:36 by codk              #+#    #+#             */
/*   Updated: 2025/05/27 17:25:35 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_convert_char_to_bit(char c)
{
	int		i;
	char	*s;

	i = 7;
	s = (char *)malloc(sizeof(char) * 9);
	if (!s)
		return (NULL);
	while (i >= 0)
	{
		s[i] = (c % 2) + 48;
		c /= 2;
		i--;
	}
	s[8] = '\n';
	return (s);
}

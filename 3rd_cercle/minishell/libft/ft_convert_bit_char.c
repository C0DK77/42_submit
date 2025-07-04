/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_bit_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:49:12 by codk              #+#    #+#             */
/*   Updated: 2025/06/26 14:37:50 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_convert_bit_to_char(char *s)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 128;
	c = '\0';
	while (j > 0)
	{
		c += (s[i] - 48) * j;
		j /= 2;
		i++;
	}
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:11:23 by corentindes       #+#    #+#             */
/*   Updated: 2024/11/20 16:28:39 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*s;

	nb = n;
	len = ft_intlen(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	s[len--] = '\0';
	if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		s[0] = '0';
	while (nb != 0)
	{
		s[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (s);
}

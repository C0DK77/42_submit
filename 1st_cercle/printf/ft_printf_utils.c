/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:06:31 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/24 12:57:46 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (count += ft_putstr("(null)"));
	while (*str)
		count += ft_putchar(*str++);
	return (count);
}

int	ft_putnbr(int nb)
{
	int		count;
	long	nbr;

	count = 0;
	nbr = nb;
	if (nbr < 0)
	{
		count += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
		count += ft_putnbr(nbr / 10);
	return (count += ft_putchar((nbr % 10) + 48));
}

int	ft_putnbr_base_long(unsigned long nbr, char *base, unsigned long lbase,
		int b)
{
	int	count;

	count = 0;
	if (nbr == 0 && b == 0)
		return (count += ft_putstr("(nil)"));
	if (b == 0)
		count += ft_putstr("0x");
	if (nbr >= lbase)
		count += ft_putnbr_base_long(nbr / lbase, base, lbase, 1);
	return (count += ft_putchar(base[nbr % lbase]));
}

int	ft_putnbr_base_int(unsigned int nbr, char *base, int b)
{
	int	count;

	count = 0;
	if (b == 0)
		count += ft_putstr("0x");
	if (nbr >= 16)
		count += ft_putnbr_base_int(nbr / 16, base, 1);
	return (count += ft_putchar(base[nbr % 16]));
}

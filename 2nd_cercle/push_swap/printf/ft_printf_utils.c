/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:06:31 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/16 17:07:11 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_printf(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (count += ft_putstr_printf("(null)"));
	while (*str)
		count += ft_putchar_printf(*str++);
	return (count);
}

int	ft_putnbr_base_long(unsigned long nbr, char *base, unsigned long lbase,
		int b)
{
	int	count;

	count = 0;
	if (nbr == 0 && b == 0)
		return (count += ft_putstr_printf("(nil)"));
	if (b == 0)
		count += ft_putstr_printf("0x");
	if (nbr >= lbase)
		count += ft_putnbr_base_long(nbr / lbase, base, lbase, 1);
	return (count += ft_putchar_printf(base[nbr % lbase]));
}

int	ft_putnbr_base_int(unsigned int nbr, char *base, int b)
{
	int	count;

	count = 0;
	if (b == 0)
		count += ft_putstr_printf("0x");
	if (nbr >= 16)
		count += ft_putnbr_base_int(nbr / 16, base, 1);
	return (count += ft_putchar_printf(base[nbr % 16]));
}

int	ft_putnbr_printf(int nb)
{
	int		count;
	long	nbr;

	count = 0;
	nbr = nb;
	if (nbr < 0)
	{
		count += ft_putchar_printf('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
		count += ft_putnbr_printf(nbr / 10);
	return (count += ft_putchar_printf((nbr % 10) + 48));
}

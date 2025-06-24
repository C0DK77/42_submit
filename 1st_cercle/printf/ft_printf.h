/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 04:08:26 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/24 12:57:23 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_var
{
	int		i;
	int		count;
	long	nbr;
}			t_var;

int			ft_printf(const char *format, ...);
int			ft_putchar(int c);
int			ft_putstr(char *str);
int			ft_putnbr(int nb);
int			ft_putnbr_base_long(unsigned long nbr, char *base,
				unsigned long lbase, int b);
int			ft_putnbr_base_int(unsigned int nbr, char *base, int b);

#endif

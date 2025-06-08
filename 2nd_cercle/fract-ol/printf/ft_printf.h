/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 04:08:26 by cdesjars          #+#    #+#             */
/*   Updated: 2025/02/12 20:05:28 by cdesjars         ###   ########.fr       */
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
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putnbr(int nb);
int			ft_putnbr_base_long(unsigned long nbr, char *base,
				unsigned long lbase, int b);
int			ft_putnbr_base_int(unsigned int nbr, char *base, int b);

#endif
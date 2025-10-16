/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:22:33 by corentindes       #+#    #+#             */
/*   Updated: 2025/10/16 16:22:51 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_all(int argc, ...)
{
	int		i;
	va_list	argv;
	char	*s;

	i = 0;
	va_start(argv, argc);
	while (i < argc)
	{
		s = va_arg(argv, void *);
		if (s)
			free(s);
		i++;
	}
	va_end(argv);
}

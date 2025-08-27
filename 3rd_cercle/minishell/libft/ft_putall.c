/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elisacid <elisacid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:39:31 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/27 21:07:54 by elisacid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putall_fd(int fd, int argc, ...)
{
	int		i;
	char	*s;
	va_list	argv;

	va_start(argv, argc);
	i = 0;
	while (i < argc)
	{
		s = va_arg(argv, char *);
		ft_putstr_fd(s, fd);
		i++;
	}
	va_end(argv);
}

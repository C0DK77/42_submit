/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_norme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:40:12 by codk              #+#    #+#             */
/*   Updated: 2025/10/07 04:40:14 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric_word(const char *s)
{
	const char	*p = s;

	if (!s || !*s)
		return (0);
	if (*p == '+' || *p == '-')
		p++;
	if (!*p)
		return (0);
	while (*p)
	{
		if (*p < '0' || *p > '9')
			return (0);
		p++;
	}
	return (1);
}

char	to_exit_u8(const char *s)
{
	int	v;

	v = ft_atoi(s);
	return ((unsigned char)v);
}

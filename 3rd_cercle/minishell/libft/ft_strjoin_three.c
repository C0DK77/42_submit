/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:45:46 by corentindes       #+#    #+#             */
/*   Updated: 2025/08/23 08:46:03 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char *t;
	char *l;

	if (!s1 || !s2 || !s3)
		return (NULL);
	t = ft_strjoin(s1, s2);
	if (!t)
		return (NULL);
	l = ft_strjoin(t, s3);
	free(t);
	return (l);
}
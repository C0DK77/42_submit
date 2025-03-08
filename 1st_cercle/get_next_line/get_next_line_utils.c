/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:29:50 by cdesjars          #+#    #+#             */
/*   Updated: 2025/02/25 12:32:29 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strcpy(char *d, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	ft_strcpy(s, s1);
	ft_strcpy(s + ft_strlen(s1), s2);
	return (free(s1), free(s2), s);
}

void	*ft_calloc(size_t cnt, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	if (cnt && len > SIZE_MAX / cnt)
		return (NULL);
	s = malloc(cnt * len);
	if (!s)
		return (NULL);
	while (i < cnt)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

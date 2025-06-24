/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:29:36 by cdesjars          #+#    #+#             */
/*   Updated: 2025/06/24 11:22:04 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*s;
	char		*l;
	char		*bf;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 1;
	while (!ft_strchr(s, '\n') && i > 0)
	{
		bf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!bf)
			return (NULL);
		i = read(fd, bf, BUFFER_SIZE);
		if ((!s && i == 0) || i == -1)
			return (free(bf), free(s), s = NULL, NULL);
		bf[i] = '\0';
		s = ft_strjoin(s, bf);
	}
	l = ft_cline(s);
	s = ft_cstack(s, l);
	return (l);
}

char	*ft_cline(char *s)
{
	char	*l;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	l = (char *)malloc(sizeof(char) * (i + 2));
	if (!l)
		return (NULL);
	i = 0;
	while (s[i])
	{
		l[i] = s[i];
		if (s[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	l[i] = '\0';
	return (l);
}

char	*ft_cstack(char *s, char *l)
{
	char	*rest;
	int		i;
	int		j;

	i = ft_strlen(l);
	if (!s[i])
		return (free(s), NULL);
	rest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!rest)
		return (NULL);
	j = 0;
	while (s[i])
		rest[j++] = s[i++];
	rest[j] = '\0';
	return (free(s), rest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:29:36 by cdesjars          #+#    #+#             */
/*   Updated: 2025/03/06 11:00:26 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*s[1024];
	char		*l;
	char		*bf;
	int			i;

	if (fd < 0 || 1024 < fd || BUFFER_SIZE <= 0)
		return (NULL);
	i = 1;
	while (!ft_strchr(s[fd], '\n') && i > 0)
	{
		bf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!bf)
			return (NULL);
		i = read(fd, bf, BUFFER_SIZE);
		if ((!s[fd] && i == 0) || i == -1)
			return (free(bf), free(s[fd]), s[fd] = NULL, NULL);
		bf[i] = '\0';
		s[fd] = ft_strjoin(s[fd], bf);
	}
	l = ft_cline(s[fd]);
	s[fd] = ft_cstack(s[fd], l);
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

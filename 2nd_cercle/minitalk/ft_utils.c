/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:18:16 by corentindes       #+#    #+#             */
/*   Updated: 2025/03/24 19:39:46 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\n';
	return (s);
}

char	*ft_convert_char_to_bit(char c)
{
	int		i;
	char	*s;

	i = 7;
	s = (char *)malloc(sizeof(char) * 9);
	if (!s)
		return (NULL);
	while (i >= 0)
	{
		s[i] = (c % 2) + 48;
		c /= 2;
		i--;
	}
	s[8] = '\n';
	return (s);
}

char ft_convert_bit_to_char(char *s)
{
	int	i;
	int j;
    int	c;

	i = 0;
	j = 128;
	while (i > 0)
	{
		c += (s[i] - 48) * i;
		i++;
		j /= 2;
	}
	return ((char)c);
}

int	main(void)
{
	printf("%c\n", ft_convert_bit_to_char("01100001"));
	return (0);
}